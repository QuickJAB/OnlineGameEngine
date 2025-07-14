#include "network/NetBase.h"

#include <chrono>

using namespace std;

NetBase::NetBase(std::atomic<bool>& in_running, float in_tickTime) : 
    m_running(in_running), m_tickTime(in_tickTime)
{
    enet_initialize();
}

NetBase::~NetBase()
{
    while (!m_incomingPacketData.empty())
    {
        enet_packet_destroy(&m_incomingPacketData.front());
        m_incomingPacketData.pop();
    }

    while (!m_outgoingPacketData.empty())
    {
        m_outgoingPacketData.pop();
    }

    enet_host_destroy(m_host);

    enet_deinitialize();
}

void NetBase::update()
{
    while (m_running.load())
    {
        while (enet_host_service(m_host, &m_event, static_cast<enet_uint32>(m_tickTime)) > 0)
        {
            switch (m_event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            case ENET_EVENT_TYPE_DISCONNECT:
            case ENET_EVENT_TYPE_RECEIVE:
                queueIncomingPacketData(m_event.packet);
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }

        enet_packet_destroy(m_event.packet);

        onNetUpdate.broadcast();

        sendPackets();
    }
}

bool NetBase::shouldQueuePacket(ENetPacket* in_packet)
{
    // Add pre-processesing of packets in overriden function
    return true;
}

void NetBase::queueIncomingPacketData(ENetPacket* in_packet)
{
    if (in_packet == nullptr || !shouldQueuePacket(in_packet)) return;

    m_incomingDataMutex.lock();
    
    m_incomingPacketData.push(*in_packet);
    
    m_incomingDataMutex.unlock();
}

void NetBase::queueOutgoingPacketData(string in_data, int in_peerIndex)
{
    if (in_data == "") return;

    m_outgoingDataMutex.lock();

    m_outgoingPacketData.push({ in_data, in_peerIndex });

    m_outgoingDataMutex.unlock();
}

queue<ENetPacket> NetBase::getIncomingPacketData()
{
    m_incomingDataMutex.lock();

    if (m_incomingPacketData.empty())
    {
        m_incomingDataMutex.unlock();
        return queue<ENetPacket>();
    }

    queue<ENetPacket> queue = m_incomingPacketData;

    while (!m_incomingPacketData.empty())
    {
        m_incomingPacketData.pop();
    }

    m_incomingDataMutex.unlock();

    return queue;
}

long long NetBase::getClockTime()
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void NetBase::sendPackets()
{
    // STUB
}