#include "GWorld.h"

#include <core/ECS/system/MovementSys.h>

GWorld::GWorld() : World()
{
	m_movementSys = new MovementSys(m_ecs);
}

GWorld::~GWorld()
{
	delete m_movementSys;
	m_movementSys = nullptr;
}

void GWorld::update(float in_dt)
{
	__super::update(in_dt);

	m_movementSys->update(in_dt);
}
