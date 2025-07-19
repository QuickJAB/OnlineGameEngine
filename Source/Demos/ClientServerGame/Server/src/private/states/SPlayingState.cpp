#include "states/SPlayingState.h"

#include <GGameState.h>
#include <GTestLevel.h>

using namespace std;

SPlayingState::SPlayingState() : GPlayingState(new GGameState())
{
}

void SPlayingState::enter()
{
	m_pLevel = new GTestLevel();
	m_pLevel->load();
}

string SPlayingState::update(const float i_cfDt)
{
	return "";
}

void SPlayingState::exit()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}
