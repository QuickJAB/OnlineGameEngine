#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include <GGameInstance.h>

class CGameInstance : public GGameInstance
{
public:
	CGameInstance();
	~CGameInstance();

	void update(float in_dt) override;

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	void quitGame() { m_running = false; }
};