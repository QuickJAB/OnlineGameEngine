#include "GTestLevel.h"

#include <core/ECS/system/MovementSys.h>
#include <core/ECS/system/CollisionSys.h>
#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/ColliderComp.h>

GTestLevel::GTestLevel() : Level()
{
	m_movementSys = new MovementSys(m_ecs);
	m_collisionSys = new CollisionSys(m_ecs);
}

GTestLevel::~GTestLevel()
{
	delete m_movementSys;
	m_movementSys = nullptr;

	delete m_collisionSys;
	m_collisionSys = nullptr;
}

void GTestLevel::update(float in_dt)
{
	__super::update(in_dt);

	m_collisionSys->update(in_dt);
	m_movementSys->update(in_dt);
}

void GTestLevel::load()
{
	// TODO: Change the logic to load from a file
	__super::load();

	uint32_t e = m_ecs->createEntity();
	TransformComp t = { e, 100, 100, 1720, 10 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 100, 970, 1720, 10 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 100, 110, 10, 860 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 1810, 110, 10, 860 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 260, 430, 10, 250 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 1660, 430, 10, 250 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 410, 555, 10, 250 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 1510, 305, 10, 250 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 560, 305, 10, 375 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 1360, 430, 10, 375 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
	e = m_ecs->createEntity();
	t = { e, 710, 535, 500, 10 };
	m_ecs->addComponent<TransformComp>(e, &t);
	m_ecs->addComponent<ColliderComp>(e);
}
