#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include <GGameInstance.h>

class Client;

class CGameInstance : public GGameInstance
{
public:
	CGameInstance() : GGameInstance() {};
	~CGameInstance() {};

	void update(float in_dt) override;
	bool init() override;
	void cleanup() override;

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHndlr = nullptr;

	void onEventQuitGameReceived() { m_shouldQuit = true; }

	Client* getClient();
};