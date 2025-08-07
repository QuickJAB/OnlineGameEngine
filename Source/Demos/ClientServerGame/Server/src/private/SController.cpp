#include "SController.h"

#include <core/ECS/component/VelocityComp.h>
#include <core/ECS/Level.h>

#include <GGamePkts.h>
#include <GTestLevel.h>

void SController::update(const float i_cfDt, ClientInputPkt& i_crPkt)
{
	VelocityComp* const cpVelocity = m_cpLevel->getComponent<VelocityComp>(m_cuEntity);

	bool bShooting;
	i_crPkt.extractFromMask(cpVelocity->fXDir, cpVelocity->fYDir, bShooting);

	GTestLevel* pLevel = static_cast<GTestLevel*>(m_cpLevel);
	pLevel->moveSpecificEntity(m_cuEntity, i_cfDt);
	pLevel->checkSpecificEntityCollisions(m_cuEntity, i_cfDt);
}
