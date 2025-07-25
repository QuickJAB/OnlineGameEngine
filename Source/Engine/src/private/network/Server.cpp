#include "network/Server.h"

using namespace std;

ENetAddress* Server::createAddress(const enet_uint16 i_cuPort)
{
    ENetAddress* address = new ENetAddress();
    address->host = ENET_HOST_ANY;
    address->port = i_cuPort;
    return address;
}

Server::Server(atomic<bool>& i_bRunning, const float i_cfTickTime, const HostConfig& i_crHostConfig) :
        NetBase(i_bRunning, i_cfTickTime, i_crHostConfig)
{
    m_muldOnNetUpdate.add(this, &Server::pingClients);
}

Server::~Server()
{
    m_muldOnNetUpdate.unbindAllFromOwner(this);

    if (m_cpHost->connectedPeers > 0)
    {
        for (int i = static_cast<int>(m_cpHost->connectedPeers) - 1; i > -1; --i)
        {
            enet_peer_disconnect(&m_cpHost->peers[i], 0);
        }
    }
}

void Server::onConnected(const ENetPacket* const)
{
    string sData = to_string(handshake) + "id" + to_string(m_uNextPlayerId);
    ++m_uNextPlayerId;
    queueOutgoingPacketData(sData, static_cast<int>(m_cpHost->connectedPeers) - 1);
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
        for (size_t i = 0; i < m_cpHost->connectedPeers; ++i)
        {
            enet_peer_send(&m_cpHost->peers[i], 0, pPacket);
        }
    }
    else if (cPktInf.iPeerIndex > -1 && cPktInf.iPeerIndex < static_cast<int>(m_cpHost->connectedPeers))
    {
        enet_peer_send(&m_cpHost->peers[cPktInf.iPeerIndex], 0, pPacket);
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

bool Server::shouldQueuePacket(const ENetPacket* const i_cpcPacket)
{
    const string csData = (const char*)i_cpcPacket->data;

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
