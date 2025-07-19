#include "states/SWaitingForPlayersState.h"

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(Server* const i_cpServer) :
    m_cpServer(i_cpServer)
{  
}

string SWaitingForPlayersState::update(const float)
{
    if (m_cpServer->getNumConnections() == m_cpServer->getMaxPlayers())
    {
        string sData = to_string(ServerCommand::startGame) + "t" + to_string(m_cpServer->getClockTime());
        m_cpServer->queueOutgoingPacketData(sData);
        return "Playing";
    }

    return "";
}