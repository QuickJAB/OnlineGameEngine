#include "network/Client.h"

using namespace std;

Client::Client(std::atomic<bool>& in_running, float in_tickTime,
    enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth) :
        NetBase(in_running, in_tickTime)
{
    m_host = enet_host_create(nullptr, 1, 1, in_inBandwidth, in_outBandwidth);
}

Client::~Client()
{
    enet_peer_disconnect_now(m_peer, 0);
    m_peer = nullptr;
}

bool Client::tryConnect(std::string in_ip, enet_uint16 in_port, uint32_t in_attemptLength)
{
    enet_address_set_host(&m_address, in_ip.c_str());
    m_address.port = in_port;

    m_peer = enet_host_connect(m_host, &m_address, 1, 0);
    if (m_peer == nullptr) return false;

    if (enet_host_service(m_host, &m_event, in_attemptLength * static_cast<enet_uint32>(1000.f)) > 0 &&
        m_event.type == ENET_EVENT_TYPE_CONNECT)
    {
        onReceiveConnection();
        return true;
    }

    enet_peer_reset(m_peer);

    enet_packet_destroy(m_event.packet);

    return false;
}

void Client::sendPackets()
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
    if (packet == nullptr) return;

    enet_peer_send(m_peer, 0, packet);
}
