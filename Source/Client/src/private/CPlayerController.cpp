#include "CPlayerController.h"

#include <SDL3/SDL_scancode.h>

#include <core/game base/Entity.h>

void CPlayerController::update(float in_dt)
{
	__super::update(in_dt);

	const bool* keyStates = m_eventHandler->getKeyStates();

	m_entity->setDir(keyStates[SDL_SCANCODE_D] - keyStates[SDL_SCANCODE_A],
		keyStates[SDL_SCANCODE_S] - keyStates[SDL_SCANCODE_W]);
}
