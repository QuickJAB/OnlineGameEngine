#include "Server.h"

#include <print>

using namespace std;
using namespace NetSettings;
using namespace NetSettings::ServerSettings;

bool Server::init()
{
    println("Initializing server...");

    // Initialize ENet
    if (enet_initialize() != 0)
    {
        println("ERROR: Failed to initalize ENet!");
        return false;
    }

    // Set up the servers address so that it can receive a connection from any IP on the Port defined in the settings
    m_address.host = ENET_HOST_ANY;
    m_address.port = NetSettings::PORT;

    // Create the ENet server object
    m_host = enet_host_create(&m_address, MAX_CONNECTIONS, NetChannel::size, IN_BANDWIDTH, OUT_BANDWIDTH);
    if (m_host == nullptr)
    {
        println("ERROR: Failed to create the host!");
        return false;
    }

    println("Server initialized!");
    
    return true;
}

void Server::update()
{
    while (m_running.load())
    {
        // Listen for new network events
        while (enet_host_service(m_host, &m_event, TICK_TIME) > 0)
        {
            switch (m_event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                onClientConnected();
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                onReceivePacket();
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                onClientDisconnected();
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }

        // Send network packets
        sendPackets();
    }
}

void Server::cleanup()
{
    // Cleanup all the unused incoming packet data
    while (!m_incomingPacketData.empty())
    {
        enet_packet_destroy(m_incomingPacketData.front());
        m_incomingPacketData.pop();
    }

    // Cleanup all the unused outgoing packet data
    while (!m_outgoingPacketData.empty())
    {
        m_outgoingPacketData.pop();
    }

    // Forcefully disconnect any remaining clients
    if (m_host->connectedPeers > 0)
    {
        for (int i = static_cast<int>(m_host->connectedPeers) - 1; i > -1; --i)
        {
            enet_peer_disconnect(&m_host->peers[i], 0);
        }
    }

    enet_host_destroy(m_host);

    enet_deinitialize();
}

void Server::onClientConnected()
{
    println("Client connected from {}", to_string(m_event.peer->address.host));
}

void Server::onReceivePacket()
{
    // NOTE TO FUTURE SELF: This function should be expanded to partially process the packet data and instantly send out
    // any data that is just being relayed through the server to other players e.g. text chat messages

    queueIncomingPacketData(m_event.packet);
}

void Server::onClientDisconnected()
{
    println("Client disconnected from {}", to_string(m_event.peer->address.host));
}

void Server::sendPackets()
{
    // Lock the queue so the game thread cannot add to it
    m_outgoingDataMutex.lock();

    if (m_outgoingPacketData.empty())
    {
        // Unlock queue so the game thread can add to it again before early returning
        m_outgoingDataMutex.unlock();
        return;
    }

    // Retrieve the oldest packet info from the queue
    const PacketInfo pktInf = m_outgoingPacketData.front();
    m_outgoingPacketData.pop();

    // Unlock queue so the game thread can add to it again
    m_outgoingDataMutex.unlock();

    // Set the reliability based on the chosen network channel (Default as unreliable)
    ENetPacketFlag pktFlag = ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT;
    if (pktInf.channel == NetChannel::reliable)
    {
        pktFlag = ENET_PACKET_FLAG_RELIABLE;
    }
    else if (pktInf.channel == NetChannel::unreliable)
    {
        pktFlag = ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT;
    }

    // Create packet from the info retrieved from the queue
    ENetPacket* packet = enet_packet_create(pktInf.data.c_str(), strlen(pktInf.data.c_str()) + 1, pktFlag);
    if (packet == nullptr)
    {
        println("WARNING: Failed to create a packet with the following payload: {}", pktInf.data);
        return;
    }

    if (pktInf.peerIndex == -1)
    {
        // Send the packet to all connected clients
        for (size_t i = 0; i < m_host->connectedPeers; ++i)
        {
            enet_peer_send(&m_host->peers[i], static_cast<enet_uint8>(pktInf.channel), packet);
        }
    }
    else if (pktInf.peerIndex > -1 && pktInf.peerIndex < static_cast<int>(m_host->connectedPeers))
    {
        enet_peer_send(&m_host->peers[pktInf.peerIndex], static_cast<enet_uint8>(pktInf.channel), packet);
    }
    else
    {
        println("WARNING: Invalid peedIndex {}! Failed to send a packet with the following payload: {}", pktInf.peerIndex, pktInf.data);
    }
}

void Server::queueIncomingPacketData(ENetPacket* in_packet)
{
    // Lock the queue from being accessed by the game thread
    m_incomingDataMutex.lock();

    // Add the ENet event to the queue of network events for the game thread to process
    m_incomingPacketData.push(in_packet);

    // Unlock the queue so it can be accessed by the game thread again
    m_incomingDataMutex.unlock();
}

void Server::queueOutgoingPacketData(std::string* in_data, int in_peerIndex, NetChannel in_channel)
{
    if (in_data == nullptr)
    {
        return;
    }

    // Lock the queue so it cannot be accessed by other threads
    m_outgoingDataMutex.lock();

    // Create and add a new PacketInfo struct to the queue
    m_outgoingPacketData.push({ *in_data, in_peerIndex, in_channel });

    // Unlock the queue so it can be accessed by other threads again
    m_outgoingDataMutex.unlock();
}
