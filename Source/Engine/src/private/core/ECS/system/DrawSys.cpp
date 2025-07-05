#include "core/ECS/system/DrawSys.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>

using namespace std;

void DrawSys::update()
{
	vector<SpriteComp>* sprites = m_ecs->getComponentArray<SpriteComp>();

	if (sprites == nullptr) return;

	ComponentContainer<TransformComp>* transforms = m_ecs->getComponentContainer<TransformComp>();
	for (SpriteComp& sprite : *sprites)
	{
		TransformComp* transform = transforms->get<TransformComp>(sprite.owner);
		if (transform == nullptr) return;

		sprite.rect.x = transform->x;
		sprite.rect.y = transform->y;
		sprite.rect.w = transform->width;
		sprite.rect.h = transform->height;
	}
}