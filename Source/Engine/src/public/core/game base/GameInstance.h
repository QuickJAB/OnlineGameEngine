#pragma once

#include "World.h"
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

	World* m_world = nullptr;
	GameMode* m_gameMode = nullptr;

private:

};