#pragma once

#include <SDL3/SDL_events.h>

#include "core/Delegates.h"

class EventHandler final
{
public:
protected:
	Delegate<void()> m_unidOnEventQuit;
	MulticastDelegate<void(const bool*)> m_muldOnKeyStatesUpdated;

private:
	SDL_Event m_Event;

	const bool* m_pKeyStates = nullptr;

public:
	EventHandler() = default;
	~EventHandler() = default;

	void pollEvents();

	const bool* getKeyStates() { return m_pKeyStates; }

protected:
private:
};
