#pragma once

#include <Controller.h>

class PlayerController : public Controller
{
public:
	PlayerController(Entity* in_entity) : Controller(in_entity) {}

	void update(float in_dt, const bool* in_keyStates) override;

private:
	float m_speed = 1.f;
	int m_direction[2] = { 0 };
};

