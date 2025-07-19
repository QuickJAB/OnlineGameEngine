#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include <core/ECS/component/SpriteComp.h>

class Renderer
{
public:
protected:
private:
	SDL_Renderer* const m_cpRenderer;

	const SDL_Color m_cClearColour = { 255, 255, 255, 255 };

public:
	Renderer(SDL_Window* const i_cpWindow);
	~Renderer();

	void draw(const std::vector<SpriteComp>* i_cpvData);

protected:
private:
};

