#include "GTestLevel.h"

#include <core/ECS/system/MovementSys.h>
#include <core/ECS/system/CollisionSys.h>
#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/ColliderComp.h>
#include <core/ECS/component/VelocityComp.h>

using namespace std;

GTestLevel::GTestLevel() : Level(),
	m_cpMovementSys(new MovementSys(m_cpECS)), m_cpCollisionSys(new CollisionSys(m_cpECS))
{
}

GTestLevel::~GTestLevel()
{
	delete m_cpMovementSys;
	delete m_cpCollisionSys;
}

void GTestLevel::update(const float i_cfDt)
{
	m_cpCollisionSys->update(i_cfDt);
	m_cpMovementSys->update(i_cfDt);
}

void GTestLevel::load()
{
	uint32_t uE = m_cpECS->createEntity();
	TransformComp t = { uE, 100, 100, 1720, 10 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 100, 970, 1720, 10 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 100, 110, 10, 860 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 1810, 110, 10, 860 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 260, 430, 10, 250 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 1660, 430, 10, 250 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 410, 555, 10, 250 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 1510, 305, 10, 250 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 560, 305, 10, 375 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 1360, 430, 10, 375 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	uE = m_cpECS->createEntity();
	t = { uE, 710, 535, 500, 10 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);

	uE = m_cpECS->createEntity();
	t = { uE, 120, 490, 100, 100 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	m_cpECS->addComponent<VelocityComp>(uE);
	m_umNetPlayerId.insert(pair<uint32_t, uint32_t>(0, uE));

	uE = m_cpECS->createEntity();
	t = { uE, 1700, 490, 100, 100 };
	m_cpECS->addComponent<TransformComp>(uE, &t);
	m_cpECS->addComponent<ColliderComp>(uE);
	m_cpECS->addComponent<VelocityComp>(uE);
	m_umNetPlayerId.insert(pair<uint32_t, uint32_t>(1, uE));
}