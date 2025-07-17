#include "GTestLevel.h"

#include <core/ECS/system/MovementSys.h>
#include <core/ECS/system/CollisionSys.h>
#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/ColliderComp.h>

GTestLevel::GTestLevel() : Level()
{
	m_pMovementSys = new MovementSys(m_pECS);
	m_pCollisionSys = new CollisionSys(m_pECS);
}

GTestLevel::~GTestLevel()
{
	delete m_pMovementSys;
	m_pMovementSys = nullptr;

	delete m_pCollisionSys;
	m_pCollisionSys = nullptr;
}

void GTestLevel::update(float i_fDt)
{
	__super::update(i_fDt);

	m_pCollisionSys->update(i_fDt);
	m_pMovementSys->update(i_fDt);
}

void GTestLevel::load()
{
	__super::load();

	uint32_t uE = m_pECS->createEntity();
	TransformComp t = { uE, 100, 100, 1720, 10 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 100, 970, 1720, 10 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 100, 110, 10, 860 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 1810, 110, 10, 860 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 260, 430, 10, 250 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 1660, 430, 10, 250 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 410, 555, 10, 250 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 1510, 305, 10, 250 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 560, 305, 10, 375 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 1360, 430, 10, 375 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
	uE = m_pECS->createEntity();
	t = { uE, 710, 535, 500, 10 };
	m_pECS->addComponent<TransformComp>(uE, &t);
	m_pECS->addComponent<ColliderComp>(uE);
}

uint32_t GTestLevel::spawnPlayer(float i_fX, float i_fY, bool i_bIsAlly)
{
	uint32_t uPlayerId = m_pECS->createEntity();
	
	TransformComp transformComp = { uPlayerId, i_fX, i_fY, 100, 100 };
	m_pECS->addComponent<TransformComp>(uPlayerId, &transformComp);

	return uPlayerId;
}