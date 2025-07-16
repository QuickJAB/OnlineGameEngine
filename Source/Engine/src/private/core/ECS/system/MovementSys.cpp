#include "core/ECS/system/MovementSys.h"

#include <vector>

#include "core/ECS/ECS.h"
#include "core/ECS/component/TransformComp.h"
#include "core/ECS/component/VelocityComp.h"

using namespace std;

void MovementSys::update(float i_fDt)
{
	vector<VelocityComp>* pvVelocities = m_pECS->getComponentArray<VelocityComp>();

	if (pvVelocities == nullptr) return;

	ComponentContainer<TransformComp>* pTransforms = m_pECS->getComponentContainer<TransformComp>();
	for (const VelocityComp& crVelocity : *pvVelocities)
	{
		TransformComp* pTransform = pTransforms->get<TransformComp>(crVelocity.uOwner);
		if (pTransform == nullptr) return;

		pTransform->fX += crVelocity.fXDir * crVelocity.fSpeed * i_fDt;
		pTransform->fY += crVelocity.fYDir * crVelocity.fSpeed * i_fDt;
	}
}
