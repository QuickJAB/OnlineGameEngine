#include "CGameInstance.h"

#include "states/CMenuState.h"
#include "states/CConnectingState.h"
#include "states/CPlayingState.h"

using namespace std;

CGameInstance::CGameInstance() : GameInstance()
{
	m_pClient = new Client(m_bRunning, 0, 0, 0);

	unordered_map<string, State*> umStates;

	CMenuState* menu = new CMenuState();
	umStates.insert(pair<string, State*>("Menu", menu));

	CConnectingState* pConnecting = new CConnectingState();
	umStates.insert(pair<string, State*>("Connecting", pConnecting));
	pConnecting->m_unidOnRequestIP.bind(menu, &CMenuState::getIP);
	pConnecting->m_unidOnRequestPort.bind(menu, &CMenuState::getPort);
	pConnecting->m_unidOnRequestClient.bind(this, &CGameInstance::getClient);
	pConnecting->m_unidOnConnectionEstablished.bind(this, &CGameInstance::startNetworkThread);
	pConnecting->m_unidOnGameStarted.bind(this, &CGameInstance::serverStartedGame);
	
	CPlayingState* pPlaying = new CPlayingState();
	umStates.insert(pair<string, State*>("Playing", pPlaying));
	pPlaying->m_unidRequestRenderer.bind(this, &CGameInstance::getRenderer);
	pPlaying->m_unidRequestEventHandler.bind(this, &CGameInstance::getEventHandler);

	m_pStateMachine = new StateMachine(umStates, "Menu");
}

CGameInstance::~CGameInstance()
{
	m_pEventHandler->m_unidOnEventQuit.unbind();
	delete m_pEventHandler;
	m_pEventHandler = nullptr;

	delete m_pRenderer;
	m_pRenderer = nullptr;

	delete m_pWindow;
	m_pWindow = nullptr;

	m_pNetworkThread->join();
	delete m_pNetworkThread;
	m_pNetworkThread = nullptr;

	delete m_pClient;
	m_pClient = nullptr;
}

void CGameInstance::initWindow()
{
	m_pWindow = new Window("OnlineGame Client", 1920, 1080);

	m_pRenderer = new Renderer(m_pWindow->getSDLWindow());

	m_pEventHandler = new EventHandler();
	m_pEventHandler->m_unidOnEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
}

void CGameInstance::startNetworkThread()
{
	thread network(&Client::update, m_pClient);
	network.detach();
	m_pNetworkThread = &network;
}

void CGameInstance::serverStartedGame(long long i_llStartTime)
{
	m_llGameStateTime = i_llStartTime;
	initWindow();
}