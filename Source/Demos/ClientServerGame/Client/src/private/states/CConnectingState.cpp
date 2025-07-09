#include "states/CConnectingState.h"

#include <print>

using namespace std;

void CConnectingState::enter()
{
    m_connected = false;
    m_ip = onRequestIP.broadcast();
    m_port = onRequestPort.broadcast();
    m_client = onRequestClient.broadcast();
}

string CConnectingState::update(float)
{
    if (!m_connected)
    {
        println("Connecting...");
        if (m_client->tryConnect(m_ip, m_port))
        {
            println("Connected!");
            println("Waiting for other players to join...");
            m_connected = true;
            onConnectionEstablished.broadcast();
        }
        else
        {
            return "Menu";
        }
    }

    return "";
}
