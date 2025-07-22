#include "CPlayerController.h"

#include <print>

#include <input/EventHandler.h>
#include <core/ECS/Level.h>
#include <core/ECS/component/VelocityComp.h>
#include <core/ECS/component/ColliderComp.h>

CPlayerController::CPlayerController(const uint32_t i_cuEntity, Level* const i_cpLevel, EventHandler* const i_cpEventHandler) :
	Controller(i_cuEntity, i_cpLevel), m_cpEventHandler(i_cpEventHandler)
{
	m_cpEventHandler->m_muldOnKeyStatesUpdated.add(this, &CPlayerController::onKeyStatesUpdated);

	m_cpLevel->getComponent<VelocityComp>(m_cuEntity)->fSpeed = 2.f;

	ColliderComp* const cpColliderComp = m_cpLevel->getComponent<ColliderComp>(m_cuEntity);
	cpColliderComp->unidOnCollided.bind(this, &CPlayerController::onCollided);
	cpColliderComp->bIsStatic = false;
}

CPlayerController::~CPlayerController()
{
	m_cpEventHandler->m_muldOnKeyStatesUpdated.unbindAllFromOwner(this);
	m_cpLevel->getComponent<ColliderComp>(m_cuEntity)->unidOnCollided.unbind();
}

void CPlayerController::onKeyStatesUpdated(const bool* i_cpKeyStates)
{
	if (m_bColliding)
	{
		m_bColliding = false;
		return;
	}

	VelocityComp* const cpVelocity = m_cpLevel->getComponent<VelocityComp>(m_cuEntity);

	cpVelocity->fXDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_D] - i_cpKeyStates[SDL_SCANCODE_A]);
	cpVelocity->fYDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_S] - i_cpKeyStates[SDL_SCANCODE_W]);
}

void CPlayerController::onCollided()
{
	VelocityComp* const cpVelocity = m_cpLevel->getComponent<VelocityComp>(m_cuEntity);
	cpVelocity->fXDir *= -2;
	cpVelocity->fYDir *= -2;
	m_bColliding = true;
}
