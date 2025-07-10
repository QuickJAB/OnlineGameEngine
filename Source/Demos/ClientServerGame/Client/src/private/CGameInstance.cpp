#include "CGameInstance.h"

#include "states/CMenuState.h"
#include "states/CConnectingState.h"
#include "states/CPlayingState.h"

using namespace std;

CGameInstance::CGameInstance() : GameInstance()
{
	m_client = new Client(m_running, 0, 0, 0);

	unordered_map<string, State*> states;

	CMenuState* menu = new CMenuState();
	states.insert(pair<string, State*>("Menu", menu));

	CConnectingState* connecting = new CConnectingState();
	states.insert(pair<string, State*>("Connecting", connecting));
	connecting->onRequestIP.bind(menu, &CMenuState::getIP);
	connecting->onRequestPort.bind(menu, &CMenuState::getPort);
	connecting->onRequestClient.bind(this, &CGameInstance::getClient);
	connecting->onConnectionEstablished.bind(this, &CGameInstance::startNetworkThread);
	connecting->onPlayerNumberReceived.bind(this, &CGameInstance::setPlayerNum);
	connecting->onGameStarted.bind(this, &CGameInstance::serverStartedGame);
	
	CPlayingState* playing = new CPlayingState();
	states.insert(pair<string, State*>("Playing", playing));
	playing->requestRenderer.bind(this, &CGameInstance::getRenderer);
	playing->requestEventHandler.bind(this, &CGameInstance::getEventHandler);

	m_stateMachine = new StateMachine(states, "Menu");
}

CGameInstance::~CGameInstance()
{
	m_eventHandler->onEventQuit.unbind();
	delete m_eventHandler;
	m_eventHandler = nullptr;

	delete m_renderer;
	m_renderer = nullptr;

	delete m_window;
	m_window = nullptr;

	m_networkThread->join();
	delete m_networkThread;
	m_networkThread = nullptr;

	delete m_client;
	m_client = nullptr;
}

void CGameInstance::initWindow()
{
	m_window = new Window("OnlineGame Client", 1920, 1080);

	m_renderer = new Renderer(m_window->getSDLWindow());

	m_eventHandler = new EventHandler();
	m_eventHandler->onEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
}

void CGameInstance::startNetworkThread()
{
	thread network(&Client::update, m_client);
	network.detach();
	m_networkThread = &network;
}

void CGameInstance::serverStartedGame(long long in_startTime)
{
	m_gameStateTime = in_startTime;
	initWindow();
}