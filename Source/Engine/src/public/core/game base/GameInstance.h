#pragma once

#include <atomic>

#include "core/ECS/Level.h"
#include "core/state machine/StateMachine.h"

class GameInstance
{
public:
protected:
	std::atomic<bool>& m_rbRunning;

	StateMachine* const m_cpStateMachine;

private:

public:
	GameInstance(std::atomic<bool>& i_rbRunning, StateMachine* const i_cpStateMachine);
	~GameInstance();

	void update(const float i_cfDt);

	bool isRunning() { return m_rbRunning.load(); }

	void quitGame() { m_rbRunning.store(false); }

protected:
private:
};