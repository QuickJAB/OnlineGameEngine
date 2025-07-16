#include "states/SPlayingState.h"

#include <GTestLevel.h>

using namespace std;

void SPlayingState::enter()
{
	m_level = new GTestLevel();
	m_level->load();
}

string SPlayingState::update(float in_dt)
{
	return "";
}

void SPlayingState::exit()
{
	delete m_level;
	m_level = nullptr;
}
