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

        if (sscanf_s(data, "%i", &pktType) > 0 && pktType == ServerCommand::startGame)
        {
            startGame(data);
            return "Playing";
        }
    }

    return "";
}

void CConnectingState::startGame(const char* in_data)
{
    long long startTime = -1;
    string format = to_string(ServerCommand::startGame) + "t%lld";
    sscanf_s(in_data, format.c_str(), &startTime);
    onGameStarted.broadcast(startTime);
}
