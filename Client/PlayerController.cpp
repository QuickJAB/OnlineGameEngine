#include "PlayerController.h"
#include <SDL3/SDL_scancode.h>

void PlayerController::update(float in_dt, const bool* in_keyStates)
{
	if (m_entity == nullptr) return;

	// Set the direction based of the key state bools of WASD keys
	m_direction[0] = in_keyStates[SDL_SCANCODE_D] - in_keyStates[SDL_SCANCODE_A];
	m_direction[1] = in_keyStates[SDL_SCANCODE_S] - in_keyStates[SDL_SCANCODE_W];

	const SDL_FRect* entRect = m_entity->getRect();

	float newX = entRect->x + (m_speed * m_direction[0] * in_dt);
	float newY = entRect->y + (m_speed * m_direction[1] * in_dt);

	m_entity->setPos(newX, newY);
}
