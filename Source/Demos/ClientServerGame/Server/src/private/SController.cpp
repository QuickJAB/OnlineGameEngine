#include "SController.h"

#include <core/ECS/component/VelocityComp.h>
#include <core/ECS/Level.h>

#include <GGamePkts.h>

void SController::update(const float i_cfDt, ClientInputPkt& i_crPkt)
{
	VelocityComp* const cpVelocity = m_cpLevel->getComponent<VelocityComp>(m_cuEntity);

	bool bShooting;
	i_crPkt.extractFromMask(cpVelocity->fXDir, cpVelocity->fYDir, bShooting);

	
}
