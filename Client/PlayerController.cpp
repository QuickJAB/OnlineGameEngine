#include "PlayerController.h"
#include <SDL3/SDL_scancode.h>
#include <Entity.h>

void PlayerController::update(float in_dt, const bool* in_keyStates)
{
	if (m_entity == nullptr) return;

	m_entity->setDir(in_keyStates[SDL_SCANCODE_D] - in_keyStates[SDL_SCANCODE_A],
		in_keyStates[SDL_SCANCODE_S] - in_keyStates[SDL_SCANCODE_W]);
}
