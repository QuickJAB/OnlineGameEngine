#pragma once

#include <core/ECS/ECS.h>

class DrawSys
{
public:
protected:
private:
	ECS* const m_cpECS = nullptr;

public:
	DrawSys(ECS* const i_cpECS) : m_cpECS(i_cpECS) {}

	void update();

protected:
private:
};