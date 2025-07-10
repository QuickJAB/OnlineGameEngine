#include "states/SWaitingForPlayersState.h"

#include <print>

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(Server* in_server) :
    m_server(in_server)
{  
}

string SWaitingForPlayersState::update(float)
{
    queue<ENetPacket> pkts = m_server->getIncomingPacketData();

    while (!pkts.empty())
    {
        ENetPacket pkt = pkts.front();
        pkts.pop();

        int pktType = -1;
        sscanf_s((const char*)pkt.data, "%i", &pktType);
        switch (pktType)
        {
        case 0:
            newClientConnected();
            break;
        default:
            break;
        }
    }

    if (m_server->getNumConnections() == m_server->getMaxPlayers())
    {
        string data = "1t" + to_string(m_server->getClockTime());
        m_server->queueOutgoingPacketData(data);
        return "Playing";
    }

    return "";
}

void SWaitingForPlayersState::newClientConnected()
{
    int playerNum = m_server->getNumConnections();
    string data = "0p" + to_string(playerNum);
    m_server->queueOutgoingPacketData(data, playerNum - 1);
}
