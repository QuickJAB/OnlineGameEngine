#include "core/ECS/system/MovementSys.h"

#include <vector>

#include "core/ECS/ECS.h"
#include "core/ECS/component/TransformComp.h"
#include "core/ECS/component/VelocityComp.h"

using namespace std;

void MovementSys::update(float in_dt)
{
	vector<VelocityComp>* velocities = m_ecs->getComponentArray<VelocityComp>();

	if (velocities == nullptr) return;

	ComponentContainer<TransformComp>* transforms = m_ecs->getComponentContainer<TransformComp>();
	for (const VelocityComp& velocity : *velocities)
	{
		TransformComp* transform = transforms->get<TransformComp>(velocity.owner);
		if (transform == nullptr) return;

		transform->x += velocity.xDir * velocity.speed * in_dt;
		transform->y += velocity.yDir * velocity.speed * in_dt;
	}
}
