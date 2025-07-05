#include "CWorld.h"

#include <core/ECS/ECS.h>
#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>

CWorld::CWorld() : GWorld()
{
	drawSys = new DrawSys(m_ecs);

	// TEST CODE START
	uint32_t e = m_ecs->createEntity();

	m_ecs->addComponent<TransformComp>(e);
	TransformComp* t = m_ecs->getComponent<TransformComp>(e);
	t->x = 100;
	t->y = 100;
	t->width = 100;
	t->height = 100;

	m_ecs->addComponent<SpriteComp>(e);
	SpriteComp* s = m_ecs->getComponent<SpriteComp>(e);
	s->colour = SDL_Color(255.f, 0.f, 0.f, 255.f);
	// TEST CODE END
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
