#include "core/game base/GameInstance.h"

using namespace std;

GameInstance::GameInstance(std::atomic<bool>& i_rbRunning, StateMachine* const i_cpStateMachine) :
	m_cpStateMachine(i_cpStateMachine), m_rbRunning(i_rbRunning)
{
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