#include "Renderer.h"
#include <iostream>

using namespace std;

bool Renderer::init(SDL_Window* in_window)
{
	// Create the renderer
	m_renderer = SDL_CreateRenderer(in_window, nullptr);
	if (m_renderer == nullptr)
	{
		cout << "ERROR: Failed to create the SDL_Renderer!\n";
		return false;
	}

	return true;
}

void Renderer::cleanup()
{
	// Empty the render arrays, the individual objects are responsible for the respective lifetimes
	m_uiRects.clear();

	// Cleanup the renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void Renderer::draw()
{
	// Clear the screen to black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	// Render UI rects
	if (!m_uiRects.empty())
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		for (const SDL_FRect* rect : m_uiRects)
		{
			SDL_RenderFillRect(m_renderer, rect);
		}
	}
	
	// Present rendered world to the window
	SDL_RenderPresent(m_renderer);
}
