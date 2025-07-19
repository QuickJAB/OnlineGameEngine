#pragma once 

#include <core/state machine/State.h>

class GGameState;
class GTestLevel;

class GPlayingState : public State
{
public:
protected:
	GGameState* const m_cpGameState;
	GTestLevel* m_pLevel = nullptr;

private:

public:
	GPlayingState(GGameState* const i_cpGameState);

protected:
private:
};