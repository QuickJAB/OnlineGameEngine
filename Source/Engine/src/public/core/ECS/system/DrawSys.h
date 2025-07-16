#pragma once

#include <core/ECS/ECS.h>

class DrawSys
{
public:
protected:
private:
	ECS* m_pECS = nullptr;

public:
	DrawSys(ECS* i_pECS) : m_pECS(i_pECS) {}

	void update();

protected:
private:
};