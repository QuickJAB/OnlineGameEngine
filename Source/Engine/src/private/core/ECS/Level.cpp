#include "core/ECS/Level.h"

#include "core/ECS/ECS.h"

Level::Level()
{
	m_ecs = new ECS();
}

Level::~Level()
{
	delete m_ecs;
	m_ecs = nullptr;
}

void Level::update(float in_dt)
{
}

void Level::load()
{
}
