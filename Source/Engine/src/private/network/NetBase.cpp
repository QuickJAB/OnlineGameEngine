#include "network/NetBase.h"

#include <print>

using namespace std;
using namespace NetSettings;

bool NetBase::init(float in_tickTime)
{
    println("Initializing network...");

    // Initialize ENet
    if (enet_initialize() != 0)
    {
        println("ERROR: Failed to initalize ENet!");
        return false;
    }

    m_tickTime = in_tickTime;

    println("Network initialized!");

    return true;
}

void NetBase::update()
{
    while (m_running.load())
    {
        // Listen for new network events
        while (enet_host_service(m_host, &m_event, m_tickTime) > 0)
        {
            switch (m_event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                onReceiveConnection();
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                onReceivePacket();
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                onReceiveDisconnection();
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }

        // Destroy the received packet
        enet_packet_destroy(m_event.packet);

        // Send network packets
        sendPackets();
    }
}

void NetBase::cleanup()
{
    // Cleanup all the unused incoming packet data
    while (!m_incomingPacketData.empty())
    {
        enet_packet_destroy(&m_incomingPacketData.front());
        m_incomingPacketData.pop();
    }

    // Cleanup all the unused outgoing packet data
    while (!m_outgoingPacketData.empty())
    {
        m_outgoingPacketData.pop();
    }

    enet_host_destroy(m_host);

    enet_deinitialize();
}

void NetBase::onReceiveConnection()
{
    queueIncomingPacketData(m_event.packet);
}

void NetBase::onReceivePacket()
{
    // NOTE TO FUTURE SELF: This function should be expanded to partially process the packet data and instantly send out
    // any data that is just being relayed through the server to other players e.g. text chat messages

    queueIncomingPacketData(m_event.packet);
}

void NetBase::onReceiveDisconnection()
{
    queueIncomingPacketData(m_event.packet);
}

void NetBase::queueIncomingPacketData(ENetPacket* in_packet)
{
    // Lock the queue from being accessed by the game thread
    m_incomingDataMutex.lock();

    // Add the ENet event to the queue of network events for the game thread to process
    m_incomingPacketData.push(*in_packet);

    // Unlock the queue so it can be accessed by the game thread again
    m_incomingDataMutex.unlock();
}

void NetBase::queueOutgoingPacketData(std::string* in_data, int in_peerIndex, NetChannel in_channel)
{
    // Lock the queue so it cannot be accessed by other threads
    m_outgoingDataMutex.lock();

    // Create and add a new PacketInfo struct to the queue
    m_outgoingPacketData.push({ *in_data, in_peerIndex, in_channel });

    // Unlock the queue so it can be accessed by other threads again
    m_outgoingDataMutex.unlock();
}