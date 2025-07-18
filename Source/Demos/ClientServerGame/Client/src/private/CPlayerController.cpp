#include "CPlayerController.h"

#include <input/EventHandler.h>
#include <core/ECS/Level.h>
#include <core/ECS/component/VelocityComp.h>

CPlayerController::CPlayerController(const uint32_t i_cuEntity, Level* i_pLevel, EventHandler* i_pEventHandler) :
	Controller(i_cuEntity, i_pLevel), m_pEventHandler(i_pEventHandler)
{
	m_pEventHandler->m_muldOnKeyStatesUpdated.add(this, &CPlayerController::onKeyStatesUpdated);
}

CPlayerController::~CPlayerController()
{
	m_pEventHandler->m_muldOnKeyStatesUpdated.unbindAllFromOwner(this);
}

void CPlayerController::onKeyStatesUpdated(const bool* i_cpKeyStates)
{
	if (m_cuEntity == (uint32_t)-1) return;

	VelocityComp* pVelocity = m_pLevel->getComponent<VelocityComp>(m_cuEntity);

	pVelocity->fXDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_D] - i_cpKeyStates[SDL_SCANCODE_A]);
	pVelocity->fYDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_S] - i_cpKeyStates[SDL_SCANCODE_W]);
}
