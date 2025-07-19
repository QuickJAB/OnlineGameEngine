#pragma once

#include <atomic>

#include "core/ECS/Level.h"
#include "core/state machine/StateMachine.h"

class GameInstance
{
public:
protected:
	std::atomic<bool> m_bRunning;

	StateMachine* const m_cpStateMachine;

private:

public:
	GameInstance(StateMachine* const i_cpStateMachine);
	~GameInstance();

	void update(const float i_cfDt);

	bool isRunning() { return m_bRunning.load(); }

	void quitGame() { m_bRunning.store(false); }

protected:
private:
};