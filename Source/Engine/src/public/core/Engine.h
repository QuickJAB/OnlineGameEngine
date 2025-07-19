#pragma once

#include "game base/GameInstance.h"

class Engine
{
public:
protected:
private:
	GameInstance* const m_cpGameInstance;

public:
	Engine(GameInstance* const i_cpGameInstance);
	~Engine();

protected:
private:
	void run();
};

