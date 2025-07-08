#include "states/CConnectingState.h"

#include <print>

using namespace std;

void CConnectingState::enter()
{
    m_ip = onRequestIP.broadcast();
    m_port = onRequestPort.broadcast();
}

string CConnectingState::update(float)
{
    system("cls");
    println("Connecting too {}:{}", m_ip, m_port);
    return "";
}
