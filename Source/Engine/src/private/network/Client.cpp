#include "network/Client.h"

#include <iostream>
#include <stdio.h>

using namespace std;

Client::Client(atomic<bool>& i_bRunning, const float i_cfTickTime,
    const enet_uint32 i_cuInBandwidth, const enet_uint32 i_cuOutBandwidth) :
    NetBase(i_bRunning, i_cfTickTime, nullptr, 1, 1, i_cuInBandwidth, i_cuOutBandwidth)
{
}

Client::~Client()
{
    enet_peer_disconnect_now(m_pPeer, 0);
    m_pPeer = nullptr;
}

bool Client::tryConnect(const string i_csIp, const enet_uint16 i_cuPort, const uint32_t i_cuAttemptLength)
{
    ENetAddress address = ENetAddress();

    enet_address_set_host(&address, i_csIp.c_str());
    address.port = i_cuPort;

    m_pPeer = enet_host_connect(m_cpHost, &address, 1, 0);
    if (m_pPeer == nullptr) return false;

    if (enet_host_service(m_cpHost, &m_Event, i_cuAttemptLength * static_cast<enet_uint32>(1000.f)) > 0 &&
        m_Event.type == ENET_EVENT_TYPE_CONNECT)
    {
        return true;
    }

    enet_peer_reset(m_pPeer);

    enet_packet_destroy(m_Event.packet);

    return false;
}

void Client::sendPackets()
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
    if (pPacket == nullptr) return;

    enet_peer_send(m_pPeer, 0, pPacket);
}

void Client::processHandshake(string i_sData)
{
    string sFormat = to_string(handshake) + "id%i";
    sscanf_s(i_sData.c_str(), sFormat.c_str(), &m_uPlayerId);
}

void Client::pongServer(const string i_csPingData)
{
    const string csFormat = to_string(ping) + "t%lld";
    unsigned long long ullPingTime;
    sscanf_s(i_csPingData.c_str(), csFormat.c_str(), &ullPingTime);

    const string csData = to_string(pong) + "id" + to_string(m_uPlayerId) + 't' + to_string(getClockTime()) + "pt" + to_string(ullPingTime);
    queueOutgoingPacketData(csData);
}

bool Client::shouldQueuePacket(const ENetPacket* const i_cpcPacket)
{
    const string csData = (const char*)i_cpcPacket->data;

    int iServerCommand;
    if (sscanf_s(csData.c_str(), "%i", &iServerCommand) > 0)
    {
        switch (iServerCommand)
        {
        case handshake:
            processHandshake(csData);
            return false;
        case ping:
            pongServer(csData);
            return false;
        }
    }

    return true;
}
