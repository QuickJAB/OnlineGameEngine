#pragma once

#include "game base/GameInstance.h"

class Engine
{
public:
protected:
private:
	GameInstance* const m_pcGameInstance;

public:
	Engine(GameInstance* const i_pcGameInstance);
	~Engine();

protected:
private:
	void run();
};

