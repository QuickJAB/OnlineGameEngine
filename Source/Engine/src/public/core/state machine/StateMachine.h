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

	void update(const float i_cfDt);

	template<typename T>
	T* const getState(const std::string i_csStateName)
	{
		if (!m_umStates.contains(i_csStateName)) return nullptr;

		return static_cast<T*>(m_umStates[i_csStateName]);
	}

protected:
private:
};