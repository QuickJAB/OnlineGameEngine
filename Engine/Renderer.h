#pragma once

#include <SDL3/SDL_render.h>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	bool init(SDL_Window* in_window);
	void cleanup();

	// Remove this in the future, all rendering calls should be done through engine code
	SDL_Renderer* getSDLRenderer() { return m_renderer; }

private:
	SDL_Renderer* m_renderer;
};

