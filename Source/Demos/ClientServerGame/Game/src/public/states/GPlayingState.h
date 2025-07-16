#pragma once 

#include <core/state machine/State.h>

class GGameState;
class GTestLevel;

class GPlayingState : public State
{
public:
protected:
	GGameState* m_pGameState = nullptr;

	GTestLevel* m_pLevel = nullptr;

private:

public:
protected:
private:
};