#include "SGameInstance.h"

#include <network/Server.h>

using namespace std;

SGameInstance::SGameInstance() : GameInstance()
{
	m_server = new Server(m_running);
	m_server->init(0.f);

	thread network(&Server::update, m_server);
	network.detach();
	networkThread = &network;
}

SGameInstance::~SGameInstance()
{
	networkThread->join();
	delete networkThread;
	networkThread = nullptr;

	m_server->cleanup();
	delete m_server;
	m_server = nullptr;
}
