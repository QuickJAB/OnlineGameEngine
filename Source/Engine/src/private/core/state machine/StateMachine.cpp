#include "core/state machine/StateMachine.h"

using namespace std;

StateMachine::StateMachine(const unordered_map<string, State*> i_cumStates, string i_sStartState) :
	m_umStates(i_cumStates), m_sCurrentState(i_sStartState)
{
	m_umStates[m_sCurrentState]->enter();
}

void StateMachine::update(const float i_cfDt)
{
	string sNextState = m_umStates[m_sCurrentState]->update(i_cfDt);
	if (sNextState != "")
	{
		m_umStates[m_sCurrentState]->exit();
		m_sCurrentState = sNextState;
		m_umStates[m_sCurrentState]->enter();
	}
}

StateMachine::~StateMachine()
{
	m_umStates[m_sCurrentState]->exit();
	m_sCurrentState = "";

	for (auto pIt = m_umStates.begin(); pIt != m_umStates.end(); ++pIt)
	{
		delete pIt->second;
	}
	m_umStates.clear();
}
