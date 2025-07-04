#pragma once

#include "game base/GameInstance.h"

class Engine
{
public:
	Engine(GameInstance* in_gameInstance = new GameInstance());
	~Engine();

private:
	GameInstance* m_gameInstance = nullptr;

	void run();
};

