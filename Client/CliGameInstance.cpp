#include "CliGameInstance.h"

#include <print>
#include <Entity.h>

#include "PlayerController.h"

using namespace std;

void CliGameInstance::update(float in_dt)
{
	m_eventHndlr->pollEvents();

	m_playerCon->update(in_dt, m_eventHndlr->getKeyStates());

	m_renderer->draw();
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

	// Temp code to create an Entity and pass it to the renderer
	m_entity = new Entity(910.f, 490.f, 100.f, 100.f);
	m_renderer->addUIRect(m_entity->getRect());

	// Temp code to create a controller to posses the entity
	m_playerCon = new PlayerController(m_entity);

	println("Initalized Client Game Instance");

	return true;
}

void CliGameInstance::cleanup()
{
	// Temp code to cleanup controller
	delete m_playerCon;
	m_playerCon = nullptr;

	// Temp code to cleanup the entity
	delete m_entity;
	m_entity = nullptr;

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
