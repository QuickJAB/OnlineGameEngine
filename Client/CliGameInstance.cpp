#include "CliGameInstance.h"

#include <print>
#include <World.h>
#include <GameMode.h>

#include "PlayerController.h"

using namespace std;

void CliGameInstance::update(float in_dt)
{
	// Get the inputs from the event handler
	m_eventHndlr->pollEvents();

	// Update the game mode and the world
	m_gameMode->update(in_dt, m_eventHndlr->getKeyStates());
	m_world->update(in_dt);

	// Gather the render data from the world and pass it to the renderer
	vector<const SDL_FRect*> renderData;
	m_world->collectRenderData(renderData);
	m_renderer->draw(renderData);
}

bool CliGameInstance::init()
{
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
	m_eventHndlr->onEventQuit.bind(this, &CliGameInstance::onEventQuitGameReceived);

	// TEMPORARY CODE START
	m_world = new World();
	Entity* entity = m_world->spawnEntity(100.f, 100.f);
	m_gameMode = new GameMode();
	PlayerController* playerController = new PlayerController("playerController");
	m_gameMode->registerController(playerController);
	m_gameMode->setControllerEntity("playerController", entity);
	// TEMPORARY CODE END

	println("Initalized Client Game Instance");

	return true;
}

void CliGameInstance::cleanup()
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
}
