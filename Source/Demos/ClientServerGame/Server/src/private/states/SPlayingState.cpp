#include "states/SPlayingState.h"

#include <print>

using namespace std;

void SPlayingState::enter()
{
	println("Game started");
}

std::string SPlayingState::update(float in_dt)
{
	return "";
}

void SPlayingState::exit()
{
}
