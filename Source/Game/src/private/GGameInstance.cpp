#include "GGameInstance.h"

#include <core/game base/World.h>
#include <core/game base/GameMode.h>

bool GGameInstance::init()
{
	return __super::init();
}

void GGameInstance::update(float in_dt)
{
	__super::update(in_dt);

	// Update the game mode and the world
	m_gameMode->update(in_dt);
	m_world->update(in_dt);
}

void GGameInstance::cleanup()
{
	__super::cleanup();
}
