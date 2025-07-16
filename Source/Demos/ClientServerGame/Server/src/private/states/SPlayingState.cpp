#include "states/SPlayingState.h"

#include <GTestLevel.h>

using namespace std;

void SPlayingState::enter()
{
	m_pLevel = new GTestLevel();
	m_pLevel->load();
}

string SPlayingState::update(float i_fDt)
{
	return "";
}

void SPlayingState::exit()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}
