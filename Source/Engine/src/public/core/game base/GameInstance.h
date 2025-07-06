#pragma once

#include <atomic>

#include "core/ECS/Level.h"
#include "GameMode.h"

class GameInstance
{
public:
	GameInstance();
	~GameInstance() = default;

	virtual void update(float in_dt);

	bool isRunning() { return m_running.load(); }

protected:
	std::atomic<bool> m_running;

	Level* m_level = nullptr;
	GameMode* m_gameMode = nullptr;

private:

};