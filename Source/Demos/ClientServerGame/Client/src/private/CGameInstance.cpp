#include "CGameInstance.h"

#include "CGameMode.h"
#include "CPlayerController.h"

CGameInstance::CGameInstance() : GameInstance()
{
	m_window = new Window("Online Game Client", 1920, 1080);

	m_renderer = new Renderer(m_window->getSDLWindow());

	m_eventHandler = new EventHandler();
	m_eventHandler->onEventQuit.bind(static_cast<GameInstance*>(this), &GameInstance::quitGame);
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