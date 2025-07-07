#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>
#include <core/game base/GameInstance.h>

#include "CTestLevel.h"

class CGameInstance : public GameInstance
{
public:
	CGameInstance();
	~CGameInstance();

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;
};