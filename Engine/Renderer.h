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

	void draw();

	void addUIRect(const SDL_FRect* in_rect) { m_uiRects.push_back(in_rect); }

private:
	SDL_Renderer* m_renderer;

	std::vector<const SDL_FRect*> m_uiRects;
};

