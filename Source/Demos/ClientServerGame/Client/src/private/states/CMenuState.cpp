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
	print("\033[2J\033[1;1H"); // Clears the terminal
	println("OnlineGame Client");
	
	print("Please enter the server IPv4 address >> ");
	cin >> m_ipAddress;

	print("Please enter the port >> ");
	cin >> m_port;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return "";
	}

	onConnectionDetailsSet.broadcast(m_ipAddress, m_port);
	return "Connecting";
}