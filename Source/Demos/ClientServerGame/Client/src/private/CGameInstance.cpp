#include "CGameInstance.h"

#include "states/CMenuState.h"
#include "states/CConnectingState.h"

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
}

void CGameInstance::initWindow()
{
	m_window = new Window("OnlineGame Client", 1920, 1080);

	m_renderer = new Renderer(m_window->getSDLWindow());

	m_eventHandler = new EventHandler();
	m_eventHandler->onEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
}
