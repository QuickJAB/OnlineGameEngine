#pragma once

#include <core/game base/Controller.h>

class EventHandler;

class CPlayerController : public Controller
{
public:
	CPlayerController(EventHandler* in_eventHandler);
	~CPlayerController();

private:
	EventHandler* m_eventHandler = nullptr;

	void onKeyStatesUpdated(const bool* keyStates);
};