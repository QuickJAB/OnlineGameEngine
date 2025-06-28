#pragma once

#include <GameInstance.h>
#include <Window.h>
#include <Renderer.h>
#include <EventHandler.h>

class CGameInstance : public GameInstance
{
public:
	CGameInstance() = default;
	~CGameInstance() = default;

	void update(float in_dt) override;
	bool init() override;
	void cleanup() override;

private:
	Window* m_window;
	Renderer* m_renderer;
	EventHandler* m_eventHndlr;

	void onEventQuitGameReceived() { m_shouldQuit = true; }
};