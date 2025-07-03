#include "ECS/system/MovementSys.h"

#include <vector>

#include "ECS/ECS.h"
#include "ECS/component/TransformComp.h"
#include "ECS/component/VelocityComp.h"

using namespace std;

void MovementSys::update(float in_dt)
{
	ComponentContainer<TransformComp>* transforms = m_ecs->getComponentContainer<TransformComp>();
	for (const VelocityComp& velocity : *m_ecs->getComponentArray<VelocityComp>())
	{
		TransformComp* transform = transforms->get<TransformComp>(velocity.owner);
		if (transform == nullptr) return;

		transform->x += velocity.xDir * velocity.speed * in_dt;
		transform->y += velocity.yDir * velocity.speed * in_dt;
	}
}
