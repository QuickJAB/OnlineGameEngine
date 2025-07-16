#pragma once

#include <states/GPlayingState.h>

class SPlayingState : public GPlayingState
{
public:
	virtual void enter() override;
	virtual std::string update(float in_dt) override;
	virtual void exit() override;
};