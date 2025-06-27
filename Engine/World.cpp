#include "World.h"

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

Entity* World::spawnEntity(float in_x, float in_y, float in_width, float in_height)
{
	Entity* entity = new Entity(in_x, in_y, in_width, in_height);
	m_entities.push_back(entity);
	return entity;
}
