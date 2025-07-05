#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include <core/ECS/component/SpriteComp.h>

class Renderer
{
public:
	Renderer(SDL_Window* in_window);
	~Renderer();

	void draw(const std::vector<SpriteComp>* in_data);

private:
	SDL_Renderer* m_renderer;
};

