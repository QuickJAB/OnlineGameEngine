#include "core/ECS/system/CollisionSys.h"

#include <vector>

#include "core/ECS/ECS.h"
#include "core/ECS/component/ColliderComp.h"
#include "core/ECS/component/TransformComp.h"

using namespace std;

CollisionSys::CollisionSys(ECS* in_ecs) : 
	m_ecs(in_ecs)
{
}

void CollisionSys::update(float in_dt)
{
	vector<ColliderComp>* colliders = m_ecs->getComponentArray<ColliderComp>();
	ComponentContainer<TransformComp>* transforms = m_ecs->getComponentContainer<TransformComp>();

	if (colliders == nullptr || transforms == nullptr) return;

	for (auto i = colliders->begin(); i != colliders->end(); ++i)
	{
		if (i->isStatic) continue;

		for (auto j = colliders->begin(); j != colliders->end(); ++j)
		{
			if (i == j) continue;

			if (checkAABB(transforms->get<TransformComp>(i->owner), transforms->get<TransformComp>(j->owner)))
			{
				i->onCollided.broadcast();
				j->onCollided.broadcast();
			}
		}
	}
}

bool CollisionSys::checkAABB(const TransformComp* a, const TransformComp* b)
{
	return	(a->x >= b->x && a->x <= b->x + b->width && a->y >= b->y && a->y <= b->y + b->height) ||
			(a->x + a->width >= b->x && a->x + a->width <= b->x + b->width && a->y >= b->y && a->y <= b->y + b->height) ||
			(a->x >= b->x && a->x <= b->x + b->width && a->y + a->height >= b->y && a->y + a->height <= b->y + b->height) ||
			(a->x + a->width >= b->x && a->x + a->width <= b->x + b->width && a->y + a->height >= b->y && a->y + a->height <= b->y + b->height);
}
