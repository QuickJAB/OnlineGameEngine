#include "CGameInstance.h"

#include "states/CMenuState.h"
#include "states/CConnectingState.h"

using namespace std;

CGameInstance::CGameInstance() : GameInstance()
{
	m_client = new Client(m_running, 0, 0, 0);

	unordered_map<string, State*> states;

	states.insert(pair<string, State*>("Menu", new CMenuState()));
	static_cast<CMenuState*>(states["Menu"])->onConnectionDetailsSet.bind(this, &CGameInstance::setIPAndPort);

	states.insert(pair<string, State*>("Connecting", new CConnectingState()));
	static_cast<CConnectingState*>(states["Connecting"])->onRequestIP.bind(this, &CGameInstance::getIP);
	static_cast<CConnectingState*>(states["Connecting"])->onRequestPort.bind(this, &CGameInstance::getPort);
	static_cast<CConnectingState*>(states["Connecting"])->onRequestClient.bind(this, &CGameInstance::getClient);
	
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

void CGameInstance::setIPAndPort(std::string in_ip, uint16_t in_port)
{
	m_ip = in_ip;
	m_port = in_port;
}

void CGameInstance::initWindow()
{
	m_window = new Window("OnlineGame Client", 1920, 1080);

	m_renderer = new Renderer(m_window->getSDLWindow());

	m_eventHandler = new EventHandler();
	m_eventHandler->onEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
}
