#pragma once

#include "game base/GameInstance.h"

class Engine
{
public:
protected:
private:
	GameInstance* m_pGameInstance = nullptr;

public:
	Engine(GameInstance* i_pGameInstance = new GameInstance());
	~Engine();

protected:
private:
	void run();
};

