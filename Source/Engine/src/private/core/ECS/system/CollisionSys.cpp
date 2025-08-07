#include "core/ECS/system/CollisionSys.h"

#include <vector>
#include <algorithm>

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

	if (pvColliders == nullptr) return;

	for (auto pI = pvColliders->begin(); pI != pvColliders->end(); ++pI)
	{
		if (pI->bIsStatic) continue;

		for (auto pJ = pvColliders->begin(); pJ != pvColliders->end(); ++pJ)
		{
			if (pI == pJ) continue;

			TransformComp* const cpAT = m_cpECS->getComponent<TransformComp>(pI->uOwner);
			TransformComp* const cpBT = m_cpECS->getComponent<TransformComp>(pJ->uOwner);
			if (cpAT != nullptr && cpBT != nullptr && checkAABB(cpAT, cpBT))
			{
				CollisionResult colRes(
					min(cpAT->fX + cpAT->fWidth, cpBT->fX + cpBT->fWidth) - max(cpAT->fX, cpBT->fX),
					min(cpAT->fY + cpAT->fHeight, cpBT->fY + cpBT->fHeight) - max(cpAT->fY, cpBT->fY)
				);

				pI->unidOnCollided.broadcast(colRes);
				pJ->unidOnCollided.broadcast(colRes);
			}
		}
	}
}

void CollisionSys::checkSpecificEntityCollisions(const uint32_t i_cuEntityId, const float i_cfDt)
{
	vector<ColliderComp>* pvColliders = m_cpECS->getComponentArray<ColliderComp>();
	ColliderComp* pEntityColComp = m_cpECS->getComponent<ColliderComp>(i_cuEntityId);
	if (pvColliders == nullptr || pEntityColComp == nullptr || pEntityColComp->bIsStatic) return;

	for (auto pIt = pvColliders->begin(); pIt != pvColliders->end(); ++pIt)
	{
		if (pIt->uOwner == pEntityColComp->uOwner) continue;

		TransformComp* const cpAT = m_cpECS->getComponent<TransformComp>(pEntityColComp->uOwner);
		TransformComp* const cpBT = m_cpECS->getComponent<TransformComp>(pIt->uOwner);
		if (cpAT != nullptr && cpBT != nullptr && checkAABB(cpAT, cpBT))
		{
			CollisionResult colRes(
				min(cpAT->fX + cpAT->fWidth, cpBT->fX + cpBT->fWidth) - max(cpAT->fX, cpBT->fX),
				min(cpAT->fY + cpAT->fHeight, cpBT->fY + cpBT->fHeight) - max(cpAT->fY, cpBT->fY)
			);

			pEntityColComp->unidOnCollided.broadcast(colRes);
			pIt->unidOnCollided.broadcast(colRes);
		}
	}
}

void CollisionSys::resolveBlockingCollision(const CollisionResult i_colRes, const float i_cfXDir,
	const float i_cfYDir, float& o_rfX, float& o_rfY)
{
	if (i_colRes.cfXOverlap < i_colRes.cfYOverlap && i_cfXDir != 0)
	{
		o_rfX += i_cfXDir > 0 ? -i_colRes.cfXOverlap : i_colRes.cfXOverlap;
	}
	else if (i_colRes.cfXOverlap >= i_colRes.cfYOverlap && i_cfYDir != 0)
	{
		o_rfY += i_cfYDir > 0 ? -i_colRes.cfYOverlap : i_colRes.cfYOverlap;
	}
}

bool CollisionSys::checkAABB(const TransformComp* const cpcA, const TransformComp* const cpcB)
{
	return cpcA->fX <= cpcB->fX + cpcB->fWidth && cpcA->fX + cpcA->fWidth >= cpcB->fX && cpcA->fY <= cpcB->fY + cpcB->fHeight && cpcA->fY + cpcA->fHeight >= cpcB->fY;
}
