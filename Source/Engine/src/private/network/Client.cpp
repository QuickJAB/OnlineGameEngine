#include "network/Client.h"

#include <iostream>
#include <stdio.h>

using namespace std;

Client::Client(atomic<bool>& i_bRunning, float i_fTickTime,
    enet_uint32 i_uInBandwidth, enet_uint32 i_uOutBandwidth) :
        NetBase(i_bRunning, i_fTickTime)
{
    m_pHost = enet_host_create(nullptr, 1, 1, i_uInBandwidth, i_uOutBandwidth);
}

Client::~Client()
{
    enet_peer_disconnect_now(m_pPeer, 0);
    m_pPeer = nullptr;
}

bool Client::tryConnect(string i_sIp, enet_uint16 i_uPort, uint32_t i_uAttemptLength)
{
    enet_address_set_host(&m_Address, i_sIp.c_str());
    m_Address.port = i_uPort;

    m_pPeer = enet_host_connect(m_pHost, &m_Address, 1, 0);
    if (m_pPeer == nullptr) return false;

    if (enet_host_service(m_pHost, &m_Event, i_uAttemptLength * static_cast<enet_uint32>(1000.f)) > 0 &&
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

void Client::pongServer(string i_sPingData)
{
    const string sFormat = to_string(ping) + "t%lld";
    long long llPingTime;
    sscanf_s(i_sPingData.c_str(), sFormat.c_str(), &llPingTime);

    string sData = to_string(pong) + "id" + to_string(m_uPlayerId) + 't' + to_string(getClockTime()) + "pt" + to_string(llPingTime);
    queueOutgoingPacketData(sData);
}

bool Client::shouldQueuePacket(ENetPacket* i_pPacket)
{
    string sData = (const char*)i_pPacket->data;

    int iServerCommand;
    if (sscanf_s(sData.c_str(), "%i", &iServerCommand) > 0)
    {
        switch (iServerCommand)
        {
        case handshake:
            processHandshake(sData);
            return false;
        case ping:
            pongServer(sData);
            return false;
        }
    }

    return true;
}
