#include "network/NetBase.h"

#include <chrono>

using namespace std;

ENetHost* const NetBase::initAndCreateHost(const ENetAddress* i_pcAddress, size_t i_ullMaxConnections,
    size_t i_ullMaxChannels, enet_uint32 i_uInBadnwidth, enet_uint32 i_uOutBandwidth)
{
    enet_initialize();
    return enet_host_create(i_pcAddress, i_ullMaxConnections, i_ullMaxChannels,
        i_uInBadnwidth, i_uOutBandwidth);
}

NetBase::NetBase(std::atomic<bool>& i_bRunning, const float i_cfTickTime, const ENetAddress* i_pcAddress,
    const size_t i_cullMaxConnections, const size_t i_cullMaxChannels, const enet_uint32 i_cuInBandwidth,
    const enet_uint32 i_cuOutBandwidth) :
        m_cpHost(initAndCreateHost(i_pcAddress, i_cullMaxConnections, i_cullMaxChannels, i_cuInBandwidth,
            i_cuOutBandwidth)),
        m_bRunning(i_bRunning), m_cfTickTime(i_cfTickTime)
{
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

    enet_host_destroy(m_cpHost);

    enet_deinitialize();
}

void NetBase::update()
{
    while (m_bRunning.load())
    {
        while (enet_host_service(m_cpHost, &m_Event, static_cast<enet_uint32>(m_cfTickTime)) > 0)
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

void NetBase::queueIncomingPacketData(const ENetPacket* const i_cpcPacket)
{
    if (i_cpcPacket == nullptr || !shouldQueuePacket(i_cpcPacket)) return;

    m_IncomingDataMutex.lock();
    
    m_qIncomingPacketData.push(*i_cpcPacket);
    
    m_IncomingDataMutex.unlock();
}

void NetBase::queueOutgoingPacketData(const string i_csData, const int i_ciPeerIndex)
{
    if (i_csData == "") return;

    m_OutgoingDataMutex.lock();

    m_qOutgoingPacketData.push({ i_csData, i_ciPeerIndex });

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