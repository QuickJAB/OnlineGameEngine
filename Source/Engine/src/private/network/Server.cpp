#include "network/Server.h"

using namespace std;

Server::Server(atomic<bool>& i_bRunning, float i_fTickTime, enet_uint16 i_uPort,
    size_t i_ullMaxConnections, enet_uint32 i_uInBandwidth, enet_uint32 i_uOutBandwidth) :
        NetBase(i_bRunning, i_fTickTime)
{
    m_Address.host = ENET_HOST_ANY;
    m_Address.port = i_uPort;

    m_uMaxPlayers = static_cast<int>(i_ullMaxConnections);

    m_muldOnNetUpdate.add(this, &Server::pingClients);

    m_pHost = enet_host_create(&m_Address, i_ullMaxConnections, 1, i_uInBandwidth, i_uOutBandwidth);
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

void Server::onConnected(ENetPacket*)
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

    ENetPacket* packet = enet_packet_create(cPktInf.sData.c_str(), strlen(cPktInf.sData.c_str()) + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    if (packet == nullptr)
    {
        return;
    }

    if (cPktInf.iPeerIndex == -1)
    {
        for (size_t i = 0; i < m_pHost->connectedPeers; ++i)
        {
            enet_peer_send(&m_pHost->peers[i], 0, packet);
        }
    }
    else if (cPktInf.iPeerIndex > -1 && cPktInf.iPeerIndex < static_cast<int>(m_pHost->connectedPeers))
    {
        enet_peer_send(&m_pHost->peers[cPktInf.iPeerIndex], 0, packet);
    }
}

void Server::pingClients()
{
    long long llClockTime = getClockTime();

    if (llClockTime < m_llLastPingTime + m_llPingDelay) return;

    m_llLastPingTime = llClockTime;

    string sData = to_string(ping) + 't' + to_string(llClockTime);
    queueOutgoingPacketData(sData);
}

void Server::updateTimeOffset(string i_sData)
{
    uint32_t uPlayerId;
    long long llPingSentTime, llPingReceivedTime;
    long long llPongReceivedTime = getClockTime();

    string sFormat = to_string(pong) + "id%it%lldpt%lld";
    sscanf_s(i_sData.c_str(), sFormat.c_str(), &uPlayerId, &llPingReceivedTime, &llPingSentTime);

    const float cfDeltaTime = (llPongReceivedTime - llPingSentTime) * 0.5f;
    const long long cllNewOffset = llPingReceivedTime - (llPingSentTime + static_cast<long long>(cfDeltaTime));

    auto pOffsetIt = m_umOffsets.find(uPlayerId);
    if (pOffsetIt == m_umOffsets.end())
    {
        ClientTimeOffset offset;
        offset.qPrevious.push(cllNewOffset);
        offset.llAverage = cllNewOffset;
        m_umOffsets.insert(pair<uint32_t, ClientTimeOffset>(uPlayerId, offset));
    }
    else
    {
        ClientTimeOffset* pOffset = &(*pOffsetIt).second;

        if (pOffset->qPrevious.size() > m_cullMaxOffsets) pOffset->qPrevious.pop();
        pOffset->qPrevious.push(cllNewOffset);

        queue<long long> qOffsets = pOffset->qPrevious;
        long long acum = 0;
        for (int i = 0; i < qOffsets.size(); ++i)
        {
            acum += qOffsets.front();
            qOffsets.pop();
        }
        pOffset->llAverage = acum / pOffset->qPrevious.size();
    }
}

bool Server::shouldQueuePacket(ENetPacket* i_pPacket)
{
    string sData = (const char*)i_pPacket->data;

    int iClientCommand;
    if (sscanf_s(sData.c_str(), "%i", &iClientCommand) > 0)
    {
        if (iClientCommand == pong)
        {
            updateTimeOffset(sData);
            return false;
        }
    }

    return true;
}
