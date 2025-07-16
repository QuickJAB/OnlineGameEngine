#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include <core/ECS/component/SpriteComp.h>

class Renderer
{
public:
protected:
private:
	SDL_Renderer* m_pRenderer;

public:
	Renderer(SDL_Window* i_pWindow);
	~Renderer();

	void draw(const std::vector<SpriteComp>* i_pvData);

protected:
private:
};

