#pragma once

#include "core/ECS/Level.h"
#include "GameMode.h"

class GameInstance
{
public:
	GameInstance() = default;
	~GameInstance() = default;

	virtual void update(float in_dt);

	bool isRunning() { return m_running; }

protected:
	bool m_running = true;

	Level* m_level = nullptr;
	GameMode* m_gameMode = nullptr;

private:

};