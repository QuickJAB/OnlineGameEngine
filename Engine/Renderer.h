#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	bool init(SDL_Window* in_window);
	void cleanup();

	void draw(std::vector<const SDL_FRect*>& in_data);

private:
	SDL_Renderer* m_renderer;
};

