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