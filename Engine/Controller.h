#pragma once

#include <Entity.h>

class Controller
{
public:
	Controller(Entity* in_entity) : m_entity(in_entity) {}
	~Controller() = default;

	virtual void update(float in_dt, const bool* in_keyStates) {}

protected:
	Entity* m_entity = nullptr;
};

