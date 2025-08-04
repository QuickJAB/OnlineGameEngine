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
	JNet::JNetPeer* const m_cpServer;

private:

public:
	GPlayingState(GGameState* const i_cpGameState, JNet::JNetPeer* const i_cpServer);

protected:
private:
};