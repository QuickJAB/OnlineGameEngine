#include "states/SWaitingForPlayersState.h"

#include <JNet/JNetPeer.h>

#include <GGamePkts.h>

using namespace std;

SWaitingForPlayersState::SWaitingForPlayersState(JNet::JNetPeer* const i_cpServer) :
    m_cpServer(i_cpServer)
{  
}

string SWaitingForPlayersState::update(const float)
{
    if (m_cpServer->areConnectionsFull())
    {
        StartMatchPkt pkt;
        JNet::JNetOutPktData pktData;
        for (uint8_t i = 0; i < m_cpServer->getMaxConnections(); ++i)
        {
            pkt.uPlayerID = i;
            pktData.sData = pkt.serialize();
            pktData.iDestID = i;
            m_cpServer->queueOutgoingPkt(pktData, true);
        }

        return "Playing";
    }

    return "";
}