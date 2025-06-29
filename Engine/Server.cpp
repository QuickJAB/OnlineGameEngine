#include "Server.h"

#include <print>

using namespace std;
using namespace NetSettings;
using namespace NetSettings::ServerSettings;

bool Server::init(float in_tickTime)
{
    if (!__super::init(in_tickTime)) return false;

    println("Initializing server...");

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

void Server::cleanup()
{
    // Forcefully disconnect any remaining clients
    if (m_host->connectedPeers > 0)
    {
        for (int i = static_cast<int>(m_host->connectedPeers) - 1; i > -1; --i)
        {
            enet_peer_disconnect(&m_host->peers[i], 0);
        }
    }

    __super::cleanup();
}

void Server::onReceiveConnection()
{
    __super::onReceiveConnection();

    println("Client connected from {}", to_string(m_event.peer->address.host));
}

void Server::onReceiveDisconnection()
{
    __super::onReceiveDisconnection();

    println("Client disconnected from {}", to_string(m_event.peer->address.host));
}

void Server::sendPackets()
{
    __super::sendPackets();

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
