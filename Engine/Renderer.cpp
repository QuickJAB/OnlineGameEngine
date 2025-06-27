#include "Renderer.h"

#include <print>

using namespace std;

bool Renderer::init(SDL_Window* in_window)
{
	// Create the renderer
	m_renderer = SDL_CreateRenderer(in_window, nullptr);
	if (m_renderer == nullptr)
	{
		println("ERROR: Failed to create the SDL_Renderer!");
		return false;
	}

	return true;
}

void Renderer::cleanup()
{
	// Cleanup the renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void Renderer::draw(vector<const SDL_FRect*>& in_data)
{
	// Clear the screen to black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	// Render given rects from in_data
	if (!in_data.empty())
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		for (const SDL_FRect* rect : in_data)
		{
			SDL_RenderFillRect(m_renderer, rect);
		}
	}
	
	// Present rendered world to the window
	SDL_RenderPresent(m_renderer);
}
