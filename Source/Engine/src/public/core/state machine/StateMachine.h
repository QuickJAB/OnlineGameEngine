#pragma once

#include <unordered_map>

#include "State.h"

class StateMachine
{
public:
protected:
private:
	std::unordered_map<std::string, State*> m_umStates;
	std::string m_sCurrentState;

public:
	StateMachine(const std::unordered_map<std::string, State*> i_cumStates, std::string i_sStartState);
	~StateMachine();

	void update(float i_fDt);

protected:
private:
};