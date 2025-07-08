#include "network/Server.h"

using namespace std;

Server::Server(std::atomic<bool>& in_running, float in_tickTime, enet_uint16 in_port,
    size_t in_maxConnections, enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth) :
        NetBase(in_running, in_tickTime)
{
    m_address.host = ENET_HOST_ANY;
    m_address.port = in_port;

    m_host = enet_host_create(&m_address, in_maxConnections, 1, in_inBandwidth, in_outBandwidth);
}

Server::~Server()
{
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
