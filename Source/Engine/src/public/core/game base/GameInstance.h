#pragma once

#include <atomic>

#include "core/ECS/Level.h"
#include "GameMode.h"
#include "core/state machine/StateMachine.h"

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	void update(float in_dt);

	bool isRunning() { return m_running.load(); }

	void quitGame() { m_running.store(false); }

protected:
	std::atomic<bool> m_running;

private:
	StateMachine* m_stateMachine = nullptr;
};