#pragma once

#include <GameInstance.h>
#include <Window.h>
#include <Renderer.h>
#include <EventHandler.h>

class Entity;
class PlayerController;

class CliGameInstance : public GameInstance
{
public:
	CliGameInstance() = default;
	~CliGameInstance() = default;

	void update(float in_dt) override;
	bool init() override;
	void cleanup() override;

private:
	Window* m_window;
	Renderer* m_renderer;
	EventHandler* m_eventHndlr;

	Entity* m_entity = nullptr;
	PlayerController* m_playerCon = nullptr;

	void onEventQuitGameReceived() { m_shouldQuit = true; }
};