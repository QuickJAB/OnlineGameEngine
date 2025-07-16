#include "states/SWaitingForPlayersState.h"

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(Server* i_pServer) :
    m_pServer(i_pServer)
{  
}

string SWaitingForPlayersState::update(float)
{
    if (m_pServer->getNumConnections() == m_pServer->getMaxPlayers())
    {
        string sData = to_string(ServerCommand::startGame) + "t" + to_string(m_pServer->getClockTime());
        m_pServer->queueOutgoingPacketData(sData);
        return "Playing";
    }

    return "";
}