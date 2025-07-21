#include "network/GameState.h"

#include "core/game base/Controller.h"

GameState::~GameState()
{
	for (auto pair : m_umControllers)
	{
		delete pair.second;
	}

	m_umControllers.clear();
}

Controller* const GameState::getController(const uint32_t i_cuEntityId)
{
	return nullptr;
}
