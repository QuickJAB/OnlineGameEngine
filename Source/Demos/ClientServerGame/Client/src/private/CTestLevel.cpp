#include "CTestLevel.h"

#include <vector>

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

using namespace std;

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

	const vector<uint32_t>* entities = m_ecs->getEntities();
	for (auto it = entities->begin(); it != entities->end(); ++it)
	{
		m_ecs->addComponent<SpriteComp>(*it);
	}
}

std::vector<SpriteComp>* CTestLevel::getSprites()
{
	return m_ecs->getComponentArray<SpriteComp>();
}
