#include "core/game base/World.h"

#include "core/ECS/ECS.h"

World::World()
{
	m_ecs = new ECS();
}

World::~World()
{
	delete m_ecs;
	m_ecs = nullptr;
}

void World::update(float in_dt)
{

}