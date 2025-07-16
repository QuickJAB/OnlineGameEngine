#include "core/ECS/system/DrawSys.h"

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>

using namespace std;

void DrawSys::update()
{
	vector<SpriteComp>* pvSprites = m_pECS->getComponentArray<SpriteComp>();

	if (pvSprites == nullptr) return;

	ComponentContainer<TransformComp>* pTransforms = m_pECS->getComponentContainer<TransformComp>();
	for (SpriteComp& rSprite : *pvSprites)
	{
		TransformComp* pTransform = pTransforms->get<TransformComp>(rSprite.uOwner);
		if (pTransform == nullptr) return;

		rSprite.rect.x = pTransform->fX;
		rSprite.rect.y = pTransform->fY;
		rSprite.rect.w = pTransform->fWidth;
		rSprite.rect.h = pTransform->fHeight;
	}
}