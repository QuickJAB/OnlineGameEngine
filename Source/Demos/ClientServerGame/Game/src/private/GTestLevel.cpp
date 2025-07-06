#include "GTestLevel.h"

#include <core/ECS/system/MovementSys.h>

GTestLevel::GTestLevel() : Level()
{
	m_movementSys = new MovementSys(m_ecs);
}

GTestLevel::~GTestLevel()
{
	delete m_movementSys;
	m_movementSys = nullptr;
}

void GTestLevel::update(float in_dt)
{
	__super::update(in_dt);

	m_movementSys->update(in_dt);
}
