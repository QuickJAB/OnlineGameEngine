#pragma once

#include <SDL3/SDL_render.h>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	bool init(SDL_Window* in_window);
	void cleanup();

	void clearScreen(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);
	void renderQueue();

private:
	SDL_Renderer* m_renderer;
};

