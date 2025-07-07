#pragma once

#include <unordered_map>

#include "State.h"

class StateMachine
{
public:
	StateMachine(const std::unordered_map<std::string, State*> in_states, std::string in_startState);
	~StateMachine();

	void update(float in_dt);

private:
	std::unordered_map<std::string, State*> m_states;
	std::string m_currentState;
};