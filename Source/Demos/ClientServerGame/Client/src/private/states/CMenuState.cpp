#include "states/CMenuState.h"

#include <print>
#include <iostream>

using namespace std;

void CMenuState::enter()
{
	m_ipAddress = "";
	m_port = 0;
}

string CMenuState::update(float)
{
	system("cls");
	println("OnlineGame Client");
	print("Please enter the server IPv4 address >> ");
	cin >> m_ipAddress;
	print("Please enter the port >> ");
	cin >> m_port;
	onConnectionDetailsSet.broadcast(m_ipAddress, m_port);
	return "Connecting";
}