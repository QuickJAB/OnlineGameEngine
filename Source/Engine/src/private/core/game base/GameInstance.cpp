#include "core/game base/GameInstance.h"

using namespace std;

GameInstance::GameInstance()
{
	m_running.store(true);
}

GameInstance::~GameInstance()
{
	delete m_stateMachine;
	m_stateMachine = nullptr;
}

void GameInstance::update(float in_dt)
{
	if (m_stateMachine == nullptr)
	{
		quitGame();
		return;
	}

	m_stateMachine->update(in_dt);
}