#include "SGameInstance.h"

#include <network/Server.h>

using namespace std;

SGameInstance::SGameInstance() : GameInstance()
{
	m_server = new Server(m_running, 0.f, 19, 2, 0, 0);

	thread network(&Server::update, m_server);
	network.detach();
	networkThread = &network;
}

SGameInstance::~SGameInstance()
{
	networkThread->join();
	delete networkThread;
	networkThread = nullptr;

	delete m_server;
	m_server = nullptr;
}
