#include "core/ECS/system/CollisionSys.h"

#include <vector>

#include "core/ECS/ECS.h"
#include "core/ECS/component/ColliderComp.h"
#include "core/ECS/component/TransformComp.h"

using namespace std;

CollisionSys::CollisionSys(ECS* const i_cpECS) : 
	m_cpECS(i_cpECS)
{
}

void CollisionSys::update(const float i_cfDt)
{
	vector<ColliderComp>* pvColliders = m_cpECS->getComponentArray<ColliderComp>();
	ComponentContainer<TransformComp>* pTransforms = m_cpECS->getComponentContainer<TransformComp>();

	if (pvColliders == nullptr || pTransforms == nullptr) return;

	for (auto pI = pvColliders->begin(); pI != pvColliders->end(); ++pI)
	{
		if (pI->bIsStatic) continue;

		for (auto pJ = pvColliders->begin(); pJ != pvColliders->end(); ++pJ)
		{
			if (pI == pJ) continue;

			if (checkAABB(pTransforms->get<TransformComp>(pI->uOwner), pTransforms->get<TransformComp>(pJ->uOwner)))
			{
				pI->unidOnCollided.broadcast();
				pJ->unidOnCollided.broadcast();
			}
		}
	}
}

bool CollisionSys::checkAABB(const TransformComp* const cpcA, const TransformComp* const cpcB)
{
	bool bCollided = cpcA->fX >= cpcB->fX && cpcA->fX <= cpcB->fX + cpcB->fWidth && cpcA->fY >= cpcB->fY && cpcA->fY <= cpcB->fY + cpcB->fHeight;
	bCollided |= cpcA->fX + cpcA->fWidth >= cpcB->fX && cpcA->fX + cpcA->fWidth <= cpcB->fX + cpcB->fWidth && cpcA->fY >= cpcB->fY && cpcA->fY <= cpcB->fY + cpcB->fHeight;
	bCollided |= cpcA->fX >= cpcB->fX && cpcA->fX <= cpcB->fX + cpcB->fWidth && cpcA->fY + cpcA->fHeight >= cpcB->fY && cpcA->fY + cpcA->fHeight <= cpcB->fY + cpcB->fHeight;
	bCollided |= cpcA->fX + cpcA->fWidth >= cpcB->fX && cpcA->fX + cpcA->fWidth <= cpcB->fX + cpcB->fWidth && cpcA->fY + cpcA->fHeight >= cpcB->fY && cpcA->fY + cpcA->fHeight <= cpcB->fY + cpcB->fHeight;

	return bCollided;
}
