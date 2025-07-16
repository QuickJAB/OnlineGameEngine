#include "core/ECS/system/CollisionSys.h"

#include <vector>

#include "core/ECS/ECS.h"
#include "core/ECS/component/ColliderComp.h"
#include "core/ECS/component/TransformComp.h"

using namespace std;

CollisionSys::CollisionSys(ECS* i_pECS) : 
	m_pECS(i_pECS)
{
}

void CollisionSys::update(float i_fDt)
{
	vector<ColliderComp>* pvColliders = m_pECS->getComponentArray<ColliderComp>();
	ComponentContainer<TransformComp>* pTransforms = m_pECS->getComponentContainer<TransformComp>();

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

bool CollisionSys::checkAABB(const TransformComp* cpA, const TransformComp* cpB)
{
	return	(cpA->fX >= cpB->fX && cpA->fX <= cpB->fX + cpB->fWidth && cpA->fY >= cpB->fY && cpA->fY <= cpB->fY + cpB->fHeight) ||
			(cpA->fX + cpA->fWidth >= cpB->fX && cpA->fX + cpA->fWidth <= cpB->fX + cpB->fWidth && cpA->fY >= cpB->fY && cpA->fY <= cpB->fY + cpB->fHeight) ||
			(cpA->fX >= cpB->fX && cpA->fX <= cpB->fX + cpB->fWidth && cpA->fY + cpA->fHeight >= cpB->fY && cpA->fY + cpA->fHeight <= cpB->fY + cpB->fHeight) ||
			(cpA->fX + cpA->fWidth >= cpB->fX && cpA->fX + cpA->fWidth <= cpB->fX + cpB->fWidth && cpA->fY + cpA->fHeight >= cpB->fY && cpA->fY + cpA->fHeight <= cpB->fY + cpB->fHeight);
}
