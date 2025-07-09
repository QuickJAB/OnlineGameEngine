#include "SGameInstance.h"

#include <network/Server.h>

#include "states/SWaitingForPlayersState.h"

using namespace std;

SGameInstance::SGameInstance() : GameInstance()
{
	m_server = new Server(m_running, 0.f, 19, 2, 0, 0);

	unordered_map<string, State*> states;

	SWaitingForPlayersState* waitingForPlayers = new SWaitingForPlayersState(m_server);
	states.insert(pair<string, State*>("WaitingForPlayers", waitingForPlayers));

	m_stateMachine = new StateMachine(states, "WaitingForPlayers");

	thread network(&Server::update, m_server);
	network.detach();
	m_networkThread = &network;
}

SGameInstance::~SGameInstance()
{
	m_networkThread->join();
	delete m_networkThread;
	m_networkThread = nullptr;

	delete m_server;
	m_server = nullptr;
}
