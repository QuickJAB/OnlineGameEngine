#pragma once

#include <atomic>

#include "core/ECS/Level.h"
#include "core/state machine/StateMachine.h"

class GameInstance
{
public:
protected:
	std::atomic<bool> m_bRunning;

	StateMachine* m_pStateMachine = nullptr;

private:

public:
	GameInstance();
	~GameInstance();

	void update(float i_fDt);

	bool isRunning() { return m_bRunning.load(); }

	void quitGame() { m_bRunning.store(false); }

protected:
private:
};