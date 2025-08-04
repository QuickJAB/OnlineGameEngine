#include "states/GPlayingState.h"

#include <JNet/JNetPeer.h>

GPlayingState::GPlayingState(GGameState* const i_cpGameState, JNet::JNetPeer* const i_cpServer) :
	m_cpGameState(i_cpGameState), m_cpServer(i_cpServer)
{
}
