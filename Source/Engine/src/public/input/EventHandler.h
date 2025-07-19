#pragma once

#include <SDL3/SDL_events.h>

#include "core/Delegates.h"

class EventHandler final
{
public:
	Delegate<void()> m_unidOnEventQuit;
	MulticastDelegate<void(const bool*)> m_muldOnKeyStatesUpdated;
protected:
private:
	SDL_Event m_Event;

	const bool* m_pcKeyStates = nullptr;

public:
	EventHandler() = default;
	~EventHandler() = default;

	void pollEvents();

	const bool* getKeyStates() { return m_pcKeyStates; }

protected:
private:
};
