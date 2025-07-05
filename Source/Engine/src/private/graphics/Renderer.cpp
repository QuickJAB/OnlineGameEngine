#include "graphics/Renderer.h"

#include <print>

using namespace std;

Renderer::Renderer(SDL_Window* in_window)
{
	m_renderer = SDL_CreateRenderer(in_window, nullptr);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void Renderer::draw(const std::vector<SpriteComp>* in_data)
{
	// Clear the screen to black
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	// Render given rects from in_data
	if (!in_data->empty())
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		for (const SpriteComp& spriteComp : *in_data)
		{
			SDL_Color color = spriteComp.colour;
			SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(m_renderer, &spriteComp.rect);
		}

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	}
	
	// Present rendered world to the window
	SDL_RenderPresent(m_renderer);
}
