#include "CTestLevel.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

CTestLevel::CTestLevel() : GTestLevel()
{
	drawSys = new DrawSys(m_ecs);
}

CTestLevel::~CTestLevel()
{
	delete drawSys;
	drawSys = nullptr;
}

void CTestLevel::update(float in_dt)
{
	__super::update(in_dt);

	drawSys->update();
}

void CTestLevel::load()
{
	__super::load();
}

std::vector<SpriteComp>* CTestLevel::getSprites()
{
	return m_ecs->getComponentArray<SpriteComp>();
}
