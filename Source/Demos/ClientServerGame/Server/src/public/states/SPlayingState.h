#pragma once

#include <core/state machine/State.h>

class SPlayingState : public State
{
public:
	virtual void enter() override;
	virtual std::string update(float in_dt) override;
	virtual void exit() override;
};