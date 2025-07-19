#include "SGameInstance.h"

#include <network/Server.h>

#include "states/SWaitingForPlayersState.h"
#include "states/SPlayingState.h"

using namespace std;

Server* const SGameInstance::initServer(atomic<bool>& i_bRunning)
{
	HostConfig hostConfig;
	hostConfig.pcAddress = Server::createAddress(19);
	hostConfig.ullMaxConnections = 2;

	return new Server(i_bRunning, 0.f, hostConfig);
}

StateMachine* const SGameInstance::initStateMachine(Server* const i_cpServer)
{
	unordered_map<string, State*> umStates;

	SWaitingForPlayersState* pWaitingForPlayers = new SWaitingForPlayersState(i_cpServer);
	umStates.insert(pair<string, State*>("WaitingForPlayers", pWaitingForPlayers));

	SPlayingState* pPlaying = new SPlayingState();
	umStates.insert(pair<string, State*>("Playing", pPlaying));

	return new StateMachine(umStates, "WaitingForPlayers");
}

SGameInstance::SGameInstance() : m_cpServer(initServer(m_bRunning)), 
	GameInstance(initStateMachine(m_cpServer)), m_cpNetworkThread(new thread(&Server::update, m_cpServer))
{
	m_cpNetworkThread->detach();
}

SGameInstance::~SGameInstance()
{
	m_cpNetworkThread->join();
	delete m_cpNetworkThread;

	delete m_cpServer;
}
