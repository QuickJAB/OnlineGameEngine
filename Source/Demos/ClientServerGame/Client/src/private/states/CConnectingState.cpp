#include "states/CConnectingState.h"

#include <print>

using namespace std;

void CConnectingState::enter()
{
    m_bConnected = false;
    m_sIp = m_unidOnRequestIP.broadcast();
    m_uPort = m_unidOnRequestPort.broadcast();
    m_pClient = m_unidOnRequestClient.broadcast();
}

string CConnectingState::update(float)
{
    if (!m_bConnected)
    {
        println("Connecting...");
        if (m_pClient->tryConnect(m_sIp, m_uPort))
        {
            println("Connected!");
            println("Waiting for other players to join...");
            m_bConnected = true;
            m_unidOnConnectionEstablished.broadcast();
        }
        else
        {
            return "Menu";
        }
    }

    queue<ENetPacket> pkts = m_pClient->getIncomingPacketData();

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

void CConnectingState::startGame(const char* i_cpData)
{
    long long llStartTime = -1;
    string sFormat = to_string(ServerCommand::startGame) + "t%lld";
    sscanf_s(i_cpData, sFormat.c_str(), &llStartTime);
    m_unidOnGameStarted.broadcast(llStartTime);
}
