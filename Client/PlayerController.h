#pragma once

#include <Controller.h>

class PlayerController : public Controller
{
public:
	PlayerController(std::string in_id) : Controller(in_id) {}

	void update(float in_dt, const bool* in_keyStates) override;
};
