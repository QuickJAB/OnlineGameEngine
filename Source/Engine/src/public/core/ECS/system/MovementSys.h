#pragma once

class ECS;

class MovementSys
{
public:
protected:
private:
	ECS* m_pECS = nullptr;

public:
	MovementSys(ECS* i_pECS) : m_pECS(i_pECS) {}

	void update(float i_fDt);
	
protected:
private:
};