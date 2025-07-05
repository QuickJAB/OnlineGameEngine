#include "core/ECS/system/DrawSys.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>

void DrawSys::update()
{
	ComponentContainer<TransformComp>* transforms = m_ecs->getComponentContainer<TransformComp>();
	for (SpriteComp& sprite : *m_ecs->getComponentArray<SpriteComp>())
	{
		TransformComp* transform = transforms->get<TransformComp>(sprite.owner);
		if (transform == nullptr) return;

		sprite.rect.x = transform->x;
		sprite.rect.y = transform->y;
		sprite.rect.w = transform->width;
		sprite.rect.h = transform->height;
	}
}