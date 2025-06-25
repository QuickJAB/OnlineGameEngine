#pragma once

#include <SDL3/SDL_events.h>
#include "Delegates.h"

class EventHandler final
{
public:
	EventHandler() = default;
	~EventHandler() = default;

	void pollEvents();

	Delegate<void()> onEventQuit;

private:
	SDL_Event m_event;

	const bool* m_keyStates = nullptr;
};
