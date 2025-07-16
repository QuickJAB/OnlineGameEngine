#include "network/NetBase.h"

#include <chrono>

using namespace std;

NetBase::NetBase(atomic<bool>& i_bRunning, float i_fTickTime) :
    m_bRunning(i_bRunning), m_fTickTime(i_fTickTime)
{
    enet_initialize();
}

NetBase::~NetBase()
{
    while (!m_qIncomingPacketData.empty())
    {
        enet_packet_destroy(&m_qIncomingPacketData.front());
        m_qIncomingPacketData.pop();
    }

    while (!m_qOutgoingPacketData.empty())
    {
        m_qOutgoingPacketData.pop();
    }

    enet_host_destroy(m_pHost);

    enet_deinitialize();
}

void NetBase::update()
{
    while (m_bRunning.load())
    {
        while (enet_host_service(m_pHost, &m_Event, static_cast<enet_uint32>(m_fTickTime)) > 0)
        {
            switch (m_Event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                onConnected(m_Event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                onDisconnected(m_Event.packet);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                queueIncomingPacketData(m_Event.packet);
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }

        enet_packet_destroy(m_Event.packet);

        m_muldOnNetUpdate.broadcast();

        sendPackets();
    }
}

bool NetBase::shouldQueuePacket(ENetPacket* i_pPacket)
{
    return true;
}

void NetBase::queueIncomingPacketData(ENetPacket* i_pPacket)
{
    if (i_pPacket == nullptr || !shouldQueuePacket(i_pPacket)) return;

    m_IncomingDataMutex.lock();
    
    m_qIncomingPacketData.push(*i_pPacket);
    
    m_IncomingDataMutex.unlock();
}

void NetBase::queueOutgoingPacketData(string i_sData, int i_iPeerIndex)
{
    if (i_sData == "") return;

    m_OutgoingDataMutex.lock();

    m_qOutgoingPacketData.push({ i_sData, i_iPeerIndex });

    m_OutgoingDataMutex.unlock();
}

queue<ENetPacket> NetBase::getIncomingPacketData()
{
    m_IncomingDataMutex.lock();

    if (m_qIncomingPacketData.empty())
    {
        m_IncomingDataMutex.unlock();
        return queue<ENetPacket>();
    }

    queue<ENetPacket> qQueue = m_qIncomingPacketData;

    while (!m_qIncomingPacketData.empty())
    {
        m_qIncomingPacketData.pop();
    }

    m_IncomingDataMutex.unlock();

    return qQueue;
}

long long NetBase::getClockTime()
{
    using namespace chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void NetBase::sendPackets()
{
}

void NetBase::onConnected(ENetPacket* i_pPacket)
{
}

void NetBase::onDisconnected(ENetPacket* i_pPacket)
{
}
