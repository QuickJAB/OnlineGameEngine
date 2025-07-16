#pragma once 

#include <core/state machine/State.h>

class GGameState;
class GTestLevel;

class GPlayingState : public State
{
protected:
	GGameState* m_gameState = nullptr;

	GTestLevel* m_level = nullptr;
};