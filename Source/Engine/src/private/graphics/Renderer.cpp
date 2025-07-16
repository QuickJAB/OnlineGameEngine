#include "graphics/Renderer.h"

using namespace std;

Renderer::Renderer(SDL_Window* i_pWindow)
{
	m_pRenderer = SDL_CreateRenderer(i_pWindow, nullptr);
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;
}

void Renderer::draw(const vector<SpriteComp>* i_pvData)
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(m_pRenderer);

	if (!i_pvData->empty())
	{
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
		for (const SpriteComp& crSpriteComp : *i_pvData)
		{
			SDL_Color color = crSpriteComp.colour;
			SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(m_pRenderer, &crSpriteComp.rect);
		}

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
	}
	
	SDL_RenderPresent(m_pRenderer);
}
