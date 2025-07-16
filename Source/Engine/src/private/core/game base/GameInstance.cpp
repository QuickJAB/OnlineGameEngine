#include "core/game base/GameInstance.h"

using namespace std;

GameInstance::GameInstance()
{
	m_bRunning.store(true);
}

GameInstance::~GameInstance()
{
	delete m_pStateMachine;
	m_pStateMachine = nullptr;
}

void GameInstance::update(float i_fDt)
{
	if (m_pStateMachine == nullptr)
	{
		quitGame();
		return;
	}

	m_pStateMachine->update(i_fDt);
}