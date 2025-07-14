#include "network/Server.h"

using namespace std;

Server::Server(std::atomic<bool>& in_running, float in_tickTime, enet_uint16 in_port,
    size_t in_maxConnections, enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth) :
        NetBase(in_running, in_tickTime)
{
    m_address.host = ENET_HOST_ANY;
    m_address.port = in_port;

    m_maxPlayers = static_cast<int>(in_maxConnections);

    onNetUpdate.add(this, &Server::pingClients);

    m_host = enet_host_create(&m_address, in_maxConnections, 1, in_inBandwidth, in_outBandwidth);
}

Server::~Server()
{
    onNetUpdate.unbindAllFromOwner(this);

    if (m_host->connectedPeers > 0)
    {
        for (int i = static_cast<int>(m_host->connectedPeers) - 1; i > -1; --i)
        {
            enet_peer_disconnect(&m_host->peers[i], 0);
        }
    }
}

void Server::sendPackets()
{
    m_outgoingDataMutex.lock();

    if (m_outgoingPacketData.empty())
    {
        m_outgoingDataMutex.unlock();
        return;
    }

    const PacketInfo pktInf = m_outgoingPacketData.front();
    m_outgoingPacketData.pop();

    m_outgoingDataMutex.unlock();

    ENetPacket* packet = enet_packet_create(pktInf.data.c_str(), strlen(pktInf.data.c_str()) + 1, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    if (packet == nullptr)
    {
        return;
    }

    if (pktInf.peerIndex == -1)
    {
        for (size_t i = 0; i < m_host->connectedPeers; ++i)
        {
            enet_peer_send(&m_host->peers[i], 0, packet);
        }
    }
    else if (pktInf.peerIndex > -1 && pktInf.peerIndex < static_cast<int>(m_host->connectedPeers))
    {
        enet_peer_send(&m_host->peers[pktInf.peerIndex], 0, packet);
    }
}

void Server::pingClients()
{
    long long clockTime = getClockTime();

    if (clockTime < m_lastPingTime + m_pingDelay) return;

    m_lastPingTime = clockTime;

    string data = to_string(ping) + 't' + to_string(clockTime);
    queueOutgoingPacketData(data);
}

void Server::updateTimOffset(string in_data)
{
    long long pingSentTime, pingReceivedTime;
    long long pongReceivedTime = getClockTime();

    string format = to_string(pong) + "t%lldpt%lld";
    sscanf_s(in_data.c_str(), format.c_str(), &pingReceivedTime, &pingSentTime);

    const long long deltaTime = (pongReceivedTime - pingSentTime) * 0.5f;
    const long long offset = pingReceivedTime - (pingSentTime + deltaTime);
}

bool Server::shouldQueuePacket(ENetPacket* in_packet)
{
    string data = (const char*)in_packet->data;

    int clientCommand;
    if (sscanf_s(data.c_str(), "%i", &clientCommand) > 0)
    {
        if (clientCommand == pong)
        {
            updateTimOffset(data);
            return false;
        }
    }

    return true;
}
