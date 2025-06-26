#pragma once

#include <SDL3/SDL_rect.h>

class Entity
{
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	~Entity() = default;

	const SDL_FRect* getRect() const { return &m_rect; };

private:
	SDL_FRect m_rect;
};

