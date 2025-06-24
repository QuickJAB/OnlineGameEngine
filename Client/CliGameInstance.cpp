#include "CliGameInstance.h"

#include <iostream>

using namespace std;

void CliGameInstance::update(float dt)
{
	// Temporary test code allowing the client to exit by closing the window
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_EVENT_QUIT)
	{
		m_shouldQuit = true;
	}

	// Temporary test code for drawing a blank window
	SDL_SetRenderDrawColor(m_renderer->getSDLRenderer(), 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(m_renderer->getSDLRenderer());

	SDL_RenderPresent(m_renderer->getSDLRenderer());
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

	cout << "Initalized Client Game Instance\n";

	return true;
}

void CliGameInstance::cleanup()
{
	// Cleanup renderer
	m_renderer->cleanup();
	delete m_renderer;
	m_renderer = nullptr;

	// Cleanup window
	m_window->cleanup();
	delete m_window;
	m_window = nullptr;
}
