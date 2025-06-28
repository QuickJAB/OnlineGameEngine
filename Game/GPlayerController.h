#pragma once

#include <Controller.h>

class GPlayerController : public Controller
{
public:
	GPlayerController(std::string in_id) : Controller(in_id) {}
	~GPlayerController() = default;

	virtual void update(float in_dt) override;
};

