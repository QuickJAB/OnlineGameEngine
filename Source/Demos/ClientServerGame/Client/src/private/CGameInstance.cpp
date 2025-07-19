#include "CGameInstance.h"

#include "states/CMenuState.h"
#include "states/CConnectingState.h"
#include "states/CPlayingState.h"

using namespace std;

StateMachine* const CGameInstance::initStateMachine(Renderer* const i_cpRenderer,
	EventHandler* const i_cpEventHandler, Client* const i_cpClient)
{
	unordered_map<string, State*> umStates;

	CMenuState* menu = new CMenuState();
	umStates.insert(pair<string, State*>("Menu", menu));

	CConnectingState* pConnecting = new CConnectingState(i_cpClient);
	umStates.insert(pair<string, State*>("Connecting", pConnecting));

	CPlayingState* pPlaying = new CPlayingState(i_cpRenderer, i_cpEventHandler);
	umStates.insert(pair<string, State*>("Playing", pPlaying));

	return new StateMachine(umStates, "Menu");
}

CGameInstance::CGameInstance() : m_cpClient(new Client(m_bRunning, 0.f, HostConfig())),
	m_cpNetworkThread(new thread(&Client::update, m_cpClient)),
	m_cpWindow(new Window("OnlineGame Client", 1920, 1080)), m_cpRenderer(new Renderer(m_cpWindow->getSDLWindow())),
	m_cpEventHandler(new EventHandler()), GameInstance(initStateMachine(m_cpRenderer, m_cpEventHandler, m_cpClient))
{
	CMenuState* const cpMenu = m_cpStateMachine->getState<CMenuState>("Menu");
	CConnectingState* const cpConnecting = m_cpStateMachine->getState<CConnectingState>("Connecting");
	CPlayingState* const cpPlaying = m_cpStateMachine->getState<CPlayingState>("Playing");

	cpConnecting->m_unidOnRequestIP.bind(cpMenu, &CMenuState::getIP);
	cpConnecting->m_unidOnRequestPort.bind(cpMenu, &CMenuState::getPort);
	cpConnecting->m_unidOnGameStarted.bind(this, &CGameInstance::serverStartedGame);

	cpPlaying->m_unidRequestNetworkId.bind(this, &CGameInstance::getNetworkId);

	m_cpNetworkThread->detach();

	m_cpEventHandler->m_unidOnEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
}

CGameInstance::~CGameInstance()
{
	m_cpEventHandler->m_unidOnEventQuit.unbind();
	delete m_cpEventHandler;

	delete m_cpRenderer;

	delete m_cpWindow;

	m_cpNetworkThread->join();
	delete m_cpNetworkThread;

	delete m_cpClient;
}

void CGameInstance::serverStartedGame()
{
	
}
