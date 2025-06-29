#pragma once

#include <SDL3/SDL_rect.h>

class Entity
{
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	~Entity() = default;

	virtual void update(float in_dt);

	const SDL_FRect* getRect() const { return &m_rect; };

	void setPos(float in_x, float in_y) { m_rect.x = in_x; m_rect.y = in_y; }
	void setDir(int in_x, int in_y) { m_dir[0] = in_x; m_dir[1] = in_y; }

private:
	SDL_FRect m_rect;
	int m_dir[2] = {0};
	float m_speed = 0.5f;
};
