#pragma once

#include <EventHandler.h>

#include <GPlayerController.h>

class CPlayerController : public GPlayerController
{
public:
	CPlayerController(std::string in_id) : GPlayerController(in_id) {}
	~CPlayerController() = default;

	void update(float in_dt) override;

	void setEventHandler(EventHandler* in_eventHandler) { m_eventHandler = in_eventHandler; }

private:
	EventHandler* m_eventHandler = nullptr;
};
