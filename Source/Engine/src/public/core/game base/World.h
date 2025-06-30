#pragma once

#include <vector>
#include <string>

#include <SDL3/SDL_rect.h>

class Entity;

class World
{
public:
	World() = default;
	~World() = default;

	void update(float in_dt);
	void collectRenderData(std::vector<const SDL_FRect*>& out_data);

	Entity* spawnEntity(std::string in_id, float in_x, float in_y, float in_width = 100.f, float in_height = 100.f);

	void getEntityPos(std::string in_id, float& out_x, float& out_y);

private:
	std::vector<Entity*> m_entities;
};
