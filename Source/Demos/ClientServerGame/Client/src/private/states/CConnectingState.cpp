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
        if (m_client->tryConnect(m_ip, m_port, 1))
        {
            m_connected = true;
        }
        else
        {
            return "Menu";
        }
    }

    return "Menu";
}
