#pragma once

#include <SDL3/SDL_rect.h>

class Entity
{
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	~Entity() = default;

	const SDL_FRect* getRect() const { return &m_rect; };
	void setPos(float in_x, float in_y) { m_rect.x = in_x; m_rect.y = in_y; }

private:
	SDL_FRect m_rect;
};

