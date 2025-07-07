#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include <GGameInstance.h>

#include "CTestLevel.h"

class CGameInstance : public GGameInstance
{
public:
	CGameInstance();
	~CGameInstance();

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	void quitGame() { m_running = false; }
};