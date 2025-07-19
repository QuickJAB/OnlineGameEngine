#pragma once

class ECS;

class MovementSys
{
public:
protected:
private:
	ECS* const m_cpECS = nullptr;

public:
	MovementSys(ECS* const i_cpECS) : m_cpECS(i_cpECS) {}

	void update(const float i_cfDt);
	
protected:
private:
};