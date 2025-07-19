#include "graphics/Renderer.h"

using namespace std;

Renderer::Renderer(SDL_Window* const i_pcWindow) :
	m_cpRenderer(SDL_CreateRenderer(i_pcWindow, nullptr))
{
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_cpRenderer);
}

void Renderer::draw(const vector<SpriteComp>* i_cpvData)
{
	SDL_SetRenderDrawColor(m_cpRenderer, m_cClearColour.r, m_cClearColour.g, m_cClearColour.b, m_cClearColour.a);
	SDL_RenderClear(m_cpRenderer);

	if (!i_cpvData->empty())
	{
		for (const SpriteComp& crSpriteComp : *i_cpvData)
		{
			const SDL_Color cColour = crSpriteComp.colour;
			SDL_SetRenderDrawColor(m_cpRenderer, cColour.r, cColour.g, cColour.b, cColour.a);
			SDL_RenderFillRect(m_cpRenderer, &crSpriteComp.rect);
		}
	}
	
	SDL_RenderPresent(m_cpRenderer);
}
