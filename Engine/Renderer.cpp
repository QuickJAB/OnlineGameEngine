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
	// Cleanup the renderer
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void Renderer::clearScreen(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}

void Renderer::renderQueue()
{
	SDL_RenderPresent(m_renderer);
}
