#include "states/SWaitingForPlayersState.h"

#include <print>

#include <network/Server.h>

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(Server* in_server) :
    m_server(in_server)
{  
}

string SWaitingForPlayersState::update(float)
{
    queue<ENetPacket> pkts = m_server->getIncomingPacketData();
    if (pkts.empty())
    {
        m_server->queueOutgoingPacketData("ping");
    }

    while (!pkts.empty())
    {
        ENetPacket pkt = pkts.front();
        pkts.pop();

        // Process packets
        println("{}", (const char*)pkt.data);
    }

    return "";
}