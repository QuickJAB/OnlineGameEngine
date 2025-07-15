#include "states/SWaitingForPlayersState.h"

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(Server* in_server) :
    m_server(in_server)
{  
}

string SWaitingForPlayersState::update(float)
{
    if (m_server->getNumConnections() == m_server->getMaxPlayers())
    {
        string data = to_string(ServerCommand::startGame) + "t" + to_string(m_server->getClockTime());
        m_server->queueOutgoingPacketData(data);
        return "Playing";
    }

    return "";
}