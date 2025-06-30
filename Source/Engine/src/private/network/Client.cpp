#include "network/Client.h"

#include <print>

using namespace std;
using namespace NetSettings;
using namespace NetSettings::ClientSettings;

bool Client::init(float in_tickTime)
{
    if (!__super::init(in_tickTime)) return false;

    println("Initializing client...");

    // Create the client ENet object
    m_host = enet_host_create(nullptr, MAX_CONNECTIONS, NetChannel::size, IN_BANDWIDTH, OUT_BANDWIDTH);
    if (m_host == nullptr)
    {
        println("ERROR: Failed to create ENet client!");
        return false;
    }

    println("Client initialized!");

    return true;
}

void Client::cleanup()
{
    // Disconnect from the server
    enet_peer_disconnect(m_peer, 0);

    __super::cleanup();
}

bool Client::tryConnect(std::string in_ip, uint32_t in_attemptLength)
{
    // Set up the address so to the server
    enet_address_set_host(&m_address, in_ip.c_str());
    m_address.port = PORT;

    // Create the server ENet object
    println("Searching for server...");
    m_peer = enet_host_connect(m_host, &m_address, NetChannel::size, 0);
    if (m_peer == nullptr)
    {
        println("ERROR: Failed to find the server!");
        return false;
    }

    // Wait to connect to the server
    println("Connecting to server...");
    if (enet_host_service(m_host, &m_event, in_attemptLength * 1000.f) > 0 && m_event.type == ENET_EVENT_TYPE_CONNECT)
    {
        onReceiveConnection();
        return true;
    }

    println("ERROR: Failed to connect to the server!");

    // Disconnect from the server
    enet_peer_reset(m_peer);

    // Destroy the disconnect packet so we can try again
    enet_packet_destroy(m_event.packet);

    return false;
}

void Client::onReceiveConnection()
{
    __super::onReceiveConnection();

    println("Connected to the server!");
}

void Client::onReceiveDisconnection()
{
    __super::onReceiveDisconnection();

    println("Disconnected from the server!");
}

void Client::sendPackets()
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

    enet_peer_send(m_peer, static_cast<enet_uint8>(pktInf.channel), packet);
}
