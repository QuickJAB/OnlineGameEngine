#include "CWorld.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

CWorld::CWorld() : GWorld()
{
	drawSys = new DrawSys(m_ecs);
}

CWorld::~CWorld()
{
	delete drawSys;
	drawSys = nullptr;
}

void CWorld::update(float in_dt)
{
	__super::update(in_dt);

	drawSys->update();
}

std::vector<SpriteComp>* CWorld::getSprites()
{
	return m_ecs->getComponentArray<SpriteComp>();
}
