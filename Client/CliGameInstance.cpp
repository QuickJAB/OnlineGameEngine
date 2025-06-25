#include "CliGameInstance.h"

#include <iostream>

using namespace std;

void CliGameInstance::update(float dt)
{
	m_eventHndlr->pollEvents();

	m_renderer->clearScreen();
	m_renderer->renderQueue();
}

bool CliGameInstance::init()
{
	cout << "Initalizing Client Game Instance...\n";

	// Create and init the window
	m_window = new Window("Client", 1920, 1080);
	if (m_window == nullptr)
	{
		cout << "ERROR: Failed to create the window!\n";
		return false;
	}

	if (!m_window->init())
	{
		cout << "ERROR: Failed to init the window!\n";
		return false;
	}

	// Create and init the renderer
	m_renderer = new Renderer();
	if (m_renderer == nullptr)
	{
		cout << "ERROR: Failed to create the renderer!\n";
		return false;
	}

	if (!m_renderer->init(m_window->getSDLWindow()))
	{
		cout << "ERROR: Failed to initalize the renderer!\n";
		return false;
	}

	// Create the event handler
	m_eventHndlr = new EventHandler();
	if (m_eventHndlr == nullptr)
	{
		cout << "ERROR: Failed to crete the event handler!\n";
		return false;
	}

	// Bind delegates to event handler
	m_eventHndlr->onEventQuit.bind(this, &CliGameInstance::onEventQuitGameReceived);

	cout << "Initalized Client Game Instance\n";

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
