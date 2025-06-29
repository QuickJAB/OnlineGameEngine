#pragma once

#include <vector>
#include <SDL3/SDL_rect.h>

class Entity;

class World
{
public:
	World() = default;
	~World() = default;

	void update(float in_dt);
	void collectRenderData(std::vector<const SDL_FRect*>& out_data);

	Entity* spawnEntity(float in_x, float in_y, float in_width = 100.f, float in_height = 100.f);

private:
	std::vector<Entity*> m_entities;
};
