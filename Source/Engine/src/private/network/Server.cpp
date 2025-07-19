#include "network/Server.h"

using namespace std;

Server::Server(atomic<bool>& i_bRunning, const float i_cfTickTime, const enet_uint16 i_cuPort,
    const size_t i_cullMaxConnections, const enet_uint32 i_cuInBandwidth, const enet_uint32 i_cuOutBandwidth) :
        NetBase(i_bRunning, i_cfTickTime), m_cuMaxPlayers(static_cast<int>(i_cullMaxConnections))
{
    m_Address.host = ENET_HOST_ANY;
    m_Address.port = i_cuPort;

    m_muldOnNetUpdate.add(this, &Server::pingClients);

    m_pHost = enet_host_create(&m_Address, i_cullMaxConnections, 1, i_cuInBandwidth, i_cuOutBandwidth);
}

Server::~Server()
{
    m_muldOnNetUpdate.unbindAllFromOwner(this);

    if (m_pHost->connectedPeers > 0)
    {
        for (int i = static_cast<int>(m_pHost->connectedPeers) - 1; i > -1; --i)
        {
            enet_peer_disconnect(&m_pHost->peers[i], 0);
        }
    }
}

void Server::onConnected(const ENetPacket*)
{
    string sData = to_string(handshake) + "id" + to_string(m_uNextPlayerId);
    ++m_uNextPlayerId;
    queueOutgoingPacketData(sData, static_cast<int>(m_pHost->connectedPeers) - 1);
}

void Server::sendPackets()
{
    m_OutgoingDataMutex.lock();

    if (m_qOutgoingPacketData.empty())
    {
        m_OutgoingDataMutex.unlock();
        return;
    }

    const PacketInfo cPktInf = m_qOutgoingPacketData.front();
    m_qOutgoingPacketData.pop();

    m_OutgoingDataMutex.unlock();

    ENetPacket* pPacket = enet_packet_create(cPktInf.sData.c_str(), strlen(cPktInf.sData.c_str()) + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    if (pPacket == nullptr)
    {
        return;
    }

    if (cPktInf.iPeerIndex == -1)
    {
        for (size_t i = 0; i < m_pHost->connectedPeers; ++i)
        {
            enet_peer_send(&m_pHost->peers[i], 0, pPacket);
        }
    }
    else if (cPktInf.iPeerIndex > -1 && cPktInf.iPeerIndex < static_cast<int>(m_pHost->connectedPeers))
    {
        enet_peer_send(&m_pHost->peers[cPktInf.iPeerIndex], 0, pPacket);
    }
}

void Server::pingClients()
{
    unsigned long long ullClockTime = getClockTime();

    if (ullClockTime < m_ullLastPingTime + m_cullPingDelay) return;

    m_ullLastPingTime = ullClockTime;

    const string csData = to_string(ping) + 't' + to_string(ullClockTime);
    queueOutgoingPacketData(csData);
}

void Server::updateTimeOffset(const string i_csData)
{
    uint32_t uPlayerId;
    unsigned long long ullPingSentTime, ullPingReceivedTime;
    const unsigned long long cullPongReceivedTime = getClockTime();

    const string csFormat = to_string(pong) + "id%it%lldpt%lld";
    sscanf_s(i_csData.c_str(), csFormat.c_str(), &uPlayerId, &ullPingReceivedTime, &ullPingSentTime);

    const float cfDeltaTime = (cullPongReceivedTime - ullPingSentTime) * 0.5f;
    const long long cllNewOffset = ullPingReceivedTime - (ullPingSentTime + static_cast<long long>(cfDeltaTime));

    auto pOffsetIt = m_umOffsets.find(uPlayerId);
    if (pOffsetIt == m_umOffsets.end())
    {
        ClientTimeOffset offset;
        offset.qPrevious.push(cllNewOffset);
        offset.ullAverage = cllNewOffset;
        m_umOffsets.insert(pair<uint32_t, ClientTimeOffset>(uPlayerId, offset));
    }
    else
    {
        ClientTimeOffset* pOffset = &(*pOffsetIt).second;

        if (pOffset->qPrevious.size() > m_cullMaxOffsets) pOffset->qPrevious.pop();
        pOffset->qPrevious.push(cllNewOffset);

        queue<unsigned long long> qOffsets = pOffset->qPrevious;
        unsigned long long ullAcum = 0;
        for (int i = 0; i < qOffsets.size(); ++i)
        {
            ullAcum += qOffsets.front();
            qOffsets.pop();
        }
        pOffset->ullAverage = ullAcum / pOffset->qPrevious.size();
    }
}

bool Server::shouldQueuePacket(const ENetPacket* i_cpPacket)
{
    const string csData = (const char*)i_cpPacket->data;

    int iClientCommand;
    if (sscanf_s(csData.c_str(), "%i", &iClientCommand) > 0)
    {
        if (iClientCommand == pong)
        {
            updateTimeOffset(csData);
            return false;
        }
    }

    return true;
}
