#include "network/Client.h"

#include <iostream>
#include <stdio.h>

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

void Client::processHandshake(std::string in_data)
{
    string format = to_string(handshake) + "id%i";
    sscanf_s(in_data.c_str(), format.c_str(), &m_playerId);
}

void Client::pongServer(string in_pingData)
{
    const string format = to_string(ping) + "t%lld";
    long long pingTime;
    sscanf_s(in_pingData.c_str(), format.c_str(), &pingTime);

    string data = to_string(pong) + "id" + to_string(m_playerId) + 't' + to_string(getClockTime()) + "pt" + to_string(pingTime);
    queueOutgoingPacketData(data);
}

bool Client::shouldQueuePacket(ENetPacket* in_packet)
{
    string data = (const char*)in_packet->data;

    int serverCommand;
    if (sscanf_s(data.c_str(), "%i", &serverCommand) > 0)
    {
        switch (serverCommand)
        {
        case handshake:
            processHandshake(data);
            return false;
        case ping:
            pongServer(data);
            return false;
        }
    }

    return true;
}
