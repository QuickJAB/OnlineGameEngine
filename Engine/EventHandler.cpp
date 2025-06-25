#include "EventHandler.h"

void EventHandler::pollEvents()
{
	SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_EVENT_QUIT:
		onEventQuit.broadcast();
		break;
	default:
		break;
	}

	m_keyStates = SDL_GetKeyboardState(nullptr);
}
