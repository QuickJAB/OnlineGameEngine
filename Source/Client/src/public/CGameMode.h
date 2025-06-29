#pragma once

#include <input/EventHandler.h>

#include <GGameMode.h>

class CGameMode : public GGameMode
{
public:
	CGameMode(EventHandler* in_eventHandler) : GGameMode(), m_eventHandler(in_eventHandler) {}
	~CGameMode() = default;

	void update(float in_dt) override;

	void registerController(Controller* in_controller) override;

private:
	EventHandler* m_eventHandler = nullptr;
};
