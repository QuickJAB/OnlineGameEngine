#pragma once

#include <core/ECS/ECS.h>

class DrawSys
{
public:
	DrawSys(ECS* in_ecs) : m_ecs(in_ecs) {}

	void update();

private:
	ECS* m_ecs = nullptr;
};