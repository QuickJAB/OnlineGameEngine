#include "core/game base/GameInstance.h"

using namespace std;

GameInstance::GameInstance(StateMachine* const i_cpStateMachine) :
	m_cpStateMachine(i_cpStateMachine)
{
	m_bRunning.store(true);
}

GameInstance::~GameInstance()
{
	delete m_cpStateMachine;
}

void GameInstance::update(float i_fDt)
{
	if (m_cpStateMachine == nullptr)
	{
		quitGame();
		return;
	}

	m_cpStateMachine->update(i_fDt);
}