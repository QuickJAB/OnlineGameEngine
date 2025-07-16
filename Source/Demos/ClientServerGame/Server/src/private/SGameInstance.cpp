#include "SGameInstance.h"

#include <network/Server.h>

#include "states/SWaitingForPlayersState.h"
#include "states/SPlayingState.h"

using namespace std;

SGameInstance::SGameInstance() : GameInstance()
{
	m_pServer = new Server(m_bRunning, 0.f, 19, 2, 0, 0);

	unordered_map<string, State*> umStates;

	SWaitingForPlayersState* pWaitingForPlayers = new SWaitingForPlayersState(m_pServer);
	umStates.insert(pair<string, State*>("WaitingForPlayers", pWaitingForPlayers));

	SPlayingState* pPlaying = new SPlayingState();
	umStates.insert(pair<string, State*>("Playing", pPlaying));

	m_pStateMachine = new StateMachine(umStates, "WaitingForPlayers");

	thread network(&Server::update, m_pServer);
	network.detach();
	m_pNetworkThread = &network;
}

SGameInstance::~SGameInstance()
{
	m_pNetworkThread->join();
	delete m_pNetworkThread;
	m_pNetworkThread = nullptr;

	delete m_pServer;
	m_pServer = nullptr;
}
