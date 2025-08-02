#include "states/CConnectingState.h"

#include <print>

#include <JNet/JNetPeer.h>

#include <GGamePkts.h>

using namespace std;

CConnectingState::CConnectingState(JNet::JNetPeer* const i_cpClient) :
    m_cpClient(i_cpClient)
{
}

void CConnectingState::enter()
{
    m_bConnected = false;
    m_sIp = m_unidOnRequestIP.broadcast();
    m_uPort = m_unidOnRequestPort.broadcast();
}

string CConnectingState::update(float)
{
    if (!m_bConnected)
    {
        println("Connecting...");
        if (m_cpClient->tryConnect(m_sIp, m_uPort))
        {
            println("Connected!");
            println("Waiting for other players to join...");
            m_bConnected = true;
            m_cpClient->m_unidProcessGamePkt.bind(this, &CConnectingState::processGamePkts);
        }
        else
        {
            return "Menu";
        }
    }
    
    m_cpClient->processIncomingPkts();
    
    return m_sNextStateID;
}

void CConnectingState::processGamePkts(JNet::JNetPktType i_pktType, JNet::JNetInPktData& i_rPktData)
{
    if (i_pktType != GPktType::StartMatch)
    {
        return;
    }

    m_cpClient->m_unidProcessGamePkt.unbind();

    StartMatchPkt pkt;
    pkt.deserialize(i_rPktData.sData);
    m_unidOnGameStarted.broadcast(pkt.uPlayerID);
    m_sNextStateID = "Playing";
}
