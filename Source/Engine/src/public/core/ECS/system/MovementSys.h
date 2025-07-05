#pragma once

class ECS;

class MovementSys
{
public:
	MovementSys(ECS* in_ecs) : m_ecs(in_ecs) {}

	void update(float in_dt);

private:
	ECS* m_ecs = nullptr;
};