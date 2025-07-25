#include "SGameInstance.h"

#include <network/Server.h>

#include "states/SWaitingForPlayersState.h"
#include "states/SPlayingState.h"

using namespace std;

StateMachine* const SGameInstance::initStateMachine(Server* const i_cpServer)
{
	unordered_map<string, State*> umStates;

	SWaitingForPlayersState* pWaitingForPlayers = new SWaitingForPlayersState(i_cpServer);
	umStates.insert(pair<string, State*>("WaitingForPlayers", pWaitingForPlayers));

	SPlayingState* pPlaying = new SPlayingState();
	umStates.insert(pair<string, State*>("Playing", pPlaying));

	return new StateMachine(umStates, "WaitingForPlayers");
}

SGameInstance::SGameInstance(std::atomic<bool>& i_rbRunning, Server* const i_cpServer) :
	GameInstance(i_rbRunning, initStateMachine(i_cpServer)), m_cpServer(i_cpServer),
	m_cpNetworkThread(new thread(&Server::update, m_cpServer))
{
	m_cpNetworkThread->detach();
}

SGameInstance::~SGameInstance()
{
	m_cpNetworkThread->join();
	delete m_cpNetworkThread;

	delete m_cpServer;
}
