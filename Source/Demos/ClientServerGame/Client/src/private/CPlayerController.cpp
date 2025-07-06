#include "CPlayerController.h"

#include <input/EventHandler.h>
#include <core/ECS/Level.h>
#include <core/ECS/component/VelocityComp.h>

CPlayerController::CPlayerController(EventHandler* in_eventHandler) : m_eventHandler(in_eventHandler)
{
	m_eventHandler->onKeyStatesUpdated.add(this, &CPlayerController::onKeyStatesUpdated);
}

CPlayerController::~CPlayerController()
{
	m_eventHandler->onKeyStatesUpdated.unbindAllFromOwner(this);
}

void CPlayerController::onKeyStatesUpdated(const bool* keyStates)
{
	if (m_entity == (uint32_t)-1) return;

	VelocityComp* velocity = m_level->getComponent<VelocityComp>(m_entity);

	velocity->xDir = static_cast<float>(keyStates[SDL_SCANCODE_D] - keyStates[SDL_SCANCODE_A]);
	velocity->yDir = static_cast<float>(keyStates[SDL_SCANCODE_S] - keyStates[SDL_SCANCODE_W]);
}
