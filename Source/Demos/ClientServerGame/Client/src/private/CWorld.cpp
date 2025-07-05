#include "CWorld.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

CWorld::CWorld() : GWorld()
{
	drawSys = new DrawSys(m_ecs);

	// TEST CODE START
	uint32_t e = m_ecs->createEntity();

	m_ecs->addComponent<TransformComp>(e);
	TransformComp* t = m_ecs->getComponent<TransformComp>(e);
	t->x = 100.f;
	t->y = 100.f;
	t->width = 100.f;
	t->height = 100.f;

	m_ecs->addComponent<SpriteComp>(e);
	SpriteComp* s = m_ecs->getComponent<SpriteComp>(e);
	s->colour = SDL_Color(255, 0, 0, 255);

	m_ecs->addComponent<VelocityComp>(e);
	VelocityComp* v = m_ecs->getComponent<VelocityComp>(e);
	v->speed = 0.5f;
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
