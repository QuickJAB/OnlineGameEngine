#include "states/CMenuState.h"

#include <print>
#include <iostream>

using namespace std;

void CMenuState::enter()
{
	m_sIpAddress = "";
	m_uPort = 0;
}

string CMenuState::update(float)
{
	print("\033[2J\033[1;1H"); // Voodoo regex shit to "clear" terminal platform independatly
	println("OnlineGame Client");
	
	print("Please enter the server IPv4 address >> ");
	cin >> m_sIpAddress;

	print("Please enter the port >> ");
	cin >> m_uPort;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return "";
	}

	return "Connecting";
}