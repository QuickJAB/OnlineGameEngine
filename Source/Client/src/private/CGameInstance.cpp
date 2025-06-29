#include "CGameInstance.h"

#include <print>

#include <core/game base/World.h>

#include "CGameMode.h"
#include "CPlayerController.h"

using namespace std;

bool CGameInstance::init()
{
	if (!__super::init()) return false;

	println("Initalizing Client Game Instance...");

	// Create and init the window
	m_window = new Window("Client", 1920, 1080);
	if (m_window == nullptr)
	{
		println("ERROR: Failed to create the window!");
		return false;
	}

	if (!m_window->init())
	{
		println("ERROR: Failed to init the window!");
		return false;
	}

	// Create and init the renderer
	m_renderer = new Renderer();
	if (m_renderer == nullptr)
	{
		println("ERROR: Failed to create the renderer!");
		return false;
	}

	if (!m_renderer->init(m_window->getSDLWindow()))
	{
		println("ERROR: Failed to initalize the renderer!");
		return false;
	}

	// Create the event handler
	m_eventHndlr = new EventHandler();
	if (m_eventHndlr == nullptr)
	{
		println("ERROR: Failed to crete the event handler!");
		return false;
	}

	// Bind delegates to event handler
	m_eventHndlr->onEventQuit.bind(this, &CGameInstance::onEventQuitGameReceived);

	// Create the world
	m_world = new World();
	if (m_world == nullptr)
	{
		println("ERROR: Failed to create the World!");
		return false;
	}

	// Create the game mode and pass it the event handler
	m_gameMode = new CGameMode(m_eventHndlr);
	if (m_gameMode == nullptr)
	{
		println("ERROR: Failed to create the Game Mode!");
		return false;
	}

	// TEMPORARY CODE START
	Entity* entity = m_world->spawnEntity(100.f, 100.f);
	CPlayerController* playerController = new CPlayerController("playerController");
	m_gameMode->registerController(playerController);
	m_gameMode->setControllerEntity("playerController", entity);
	// TEMPORARY CODE END

	println("Initalized Client Game Instance");

	return true;
}

void CGameInstance::update(float in_dt)
{
	// Get inputs
	m_eventHndlr->pollEvents();

	// Update the game
	__super::update(in_dt);

	// Pass render data from the world to the renderer
	vector<const SDL_FRect*> renderData;
	m_world->collectRenderData(renderData);
	m_renderer->draw(renderData);
}

void CGameInstance::cleanup()
{
	// Unbind delegates from event handler
	m_eventHndlr->onEventQuit.unbind();

	// Cleanup event handler
	delete m_eventHndlr;
	m_eventHndlr = nullptr;

	// Cleanup renderer
	m_renderer->cleanup();
	delete m_renderer;
	m_renderer = nullptr;

	// Cleanup window
	m_window->cleanup();
	delete m_window;
	m_window = nullptr;

	__super::cleanup();
}
