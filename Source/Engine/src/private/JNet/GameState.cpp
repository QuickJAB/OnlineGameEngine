#include "jNet/GameState.h"

#include "core/game base/Controller.h"

GameState::~GameState()
{
	for (Controller* const cpController : m_vControllers)
	{
		delete cpController;
	}

	m_vControllers.clear();
}

void GameState::addController(Controller* const i_cpController)
{
	m_vControllers.push_back(i_cpController);
}
