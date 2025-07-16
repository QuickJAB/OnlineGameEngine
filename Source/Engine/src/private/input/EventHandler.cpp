#include "input/EventHandler.h"

void EventHandler::pollEvents()
{
	SDL_PollEvent(&m_Event);
	switch (m_Event.type)
	{
	case SDL_EVENT_QUIT:
		m_unidOnEventQuit.broadcast();
		break;
	default:
		break;
	}

	m_pKeyStates = SDL_GetKeyboardState(nullptr);
	m_muldOnKeyStatesUpdated.broadcast(m_pKeyStates);
}
