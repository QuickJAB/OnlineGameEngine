#include "states/CConnectingState.h"

#include <print>

using namespace std;

void CConnectingState::enter()
{
    m_connected = false;
    m_ip = onRequestIP.broadcast();
    m_port = onRequestPort.broadcast();
    m_client = onRequestClient.broadcast();
}

string CConnectingState::update(float)
{
    if (!m_connected)
    {
        println("Connecting...");
        if (m_client->tryConnect(m_ip, m_port))
        {
            println("Connected!");
            println("Waiting for other players to join...");
            m_connected = true;
            onConnectionEstablished.broadcast();
        }
        else
        {
            return "Menu";
        }
    }

    queue<ENetPacket> pkts = m_client->getIncomingPacketData();

    while (!pkts.empty())
    {
        ENetPacket pkt = pkts.front();
        pkts.pop();

        int pktType = -1;
        const char* data = (const char*)pkt.data;
        sscanf_s(data, "%i", &pktType);
        switch (pktType)
        {
        case 0:
            setPlayerNum(data);
            break;
        case 1:
            startGame(data);
            return "Playing";
        default:
            break;
        }
    }

    return "";
}

void CConnectingState::setPlayerNum(const char* data)
{
    int playerNum = -1;
    sscanf_s(data, "0p%i", &playerNum);
    onPlayerNumberReceived.broadcast(playerNum);
}

void CConnectingState::startGame(const char* in_data)
{
    long long startTime = -1;
    sscanf_s(in_data, "1t%lld", &startTime);
    onGameStarted.broadcast(startTime);
}
