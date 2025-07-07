#include "core/state machine/StateMachine.h"

using namespace std;

StateMachine::StateMachine(const std::unordered_map<std::string, State*> in_states, std::string in_startState) :
	m_states(in_states), m_currentState(in_startState)
{
	m_states[m_currentState]->enter();
}

void StateMachine::update(float in_dt)
{
	std::string nextState = m_states[m_currentState]->update(in_dt);
	if (nextState != "")
	{
		m_states[m_currentState]->exit();
		m_currentState = nextState;
		m_states[m_currentState]->enter();
	}
}

StateMachine::~StateMachine()
{
	m_states[m_currentState]->exit();
	m_currentState = -1;

	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		delete it->second;
	}
	m_states.clear();
}
