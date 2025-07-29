#include "states/CConnectingState.h"

#include <print>

#include <JNet/JNetPeer.h>

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
        }
        else
        {
            return "Menu";
        }
    }
    
    // TODO: Rework game start packet to comply with JNet
    //queue<ENetPacket> qPkts = m_cpClient->getIncomingPacketData();

    //while (!qPkts.empty())
    //{
    //    ENetPacket pkt = qPkts.front();
    //    qPkts.pop();

    //    int iPktType = -1;
    //    const char* cpData = (const char*)pkt.data;

    //    if (sscanf_s(cpData, "%i", &iPktType) > 0 && iPktType == ServerCommand::startGame)
    //    {
    //        startGame(cpData);
    //        return "Playing";
    //    }
    //}

    return "";
}

void CConnectingState::startGame(const char* i_cpData)
{
    m_unidOnGameStarted.broadcast();
}
