#include "core/game base/World.h"

#include <string>

#include "core/game base/Entity.h"

using namespace std;

void World::update(float in_dt)
{
	for (Entity* entity : m_entities)
	{
		entity->update(in_dt);
	}
}

void World::collectRenderData(vector<const SDL_FRect*>& out_data)
{
	for (Entity* entity : m_entities)
	{
		out_data.push_back(entity->getRect());
	}
}

Entity* World::spawnEntity(string in_id, float in_x, float in_y, float in_width, float in_height)
{
	Entity* entity = new Entity(in_id, in_x, in_y, in_width, in_height);
	m_entities.push_back(entity);
	return entity;
}

void World::getEntityPos(string in_id, float& out_x, float& out_y)
{
	for (const Entity* entity : m_entities)
	{
		if (entity->getId() == in_id)
		{
			const SDL_FRect* rect = entity->getRect();
			out_x = rect->x;
			out_y = rect->y;
			return;
		}
	}
}