#include "states/SWaitingForPlayersState.h"

#include <JNet/JNetPeer.h>

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(JNet::JNetPeer* const i_cpServer) :
    m_cpServer(i_cpServer)
{  
}

string SWaitingForPlayersState::update(const float)
{
    if (m_cpServer->areConnectionsFull())
    {
        // TODO: Rewrite connecting packet logic to fit JNet
        //string sData = to_string(ServerCommand::startGame) + "t" + to_string(m_cpServer->getClockTime());
        //m_cpServer->queueOutgoingPacketData(sData);
        return "Playing";
    }

    return "";
}