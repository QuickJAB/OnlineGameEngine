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

void Renderer::draw(const vector<SpriteComp>* i_cpvData)
{
	SDL_SetRenderDrawColor(m_pRenderer, m_cClearColour.r, m_cClearColour.g, m_cClearColour.b, m_cClearColour.a);
	SDL_RenderClear(m_pRenderer);

	if (!i_cpvData->empty())
	{
		for (const SpriteComp& crSpriteComp : *i_cpvData)
		{
			const SDL_Color cColour = crSpriteComp.colour;
			SDL_SetRenderDrawColor(m_pRenderer, cColour.r, cColour.g, cColour.b, cColour.a);
			SDL_RenderFillRect(m_pRenderer, &crSpriteComp.rect);
		}
	}
	
	SDL_RenderPresent(m_pRenderer);
}
