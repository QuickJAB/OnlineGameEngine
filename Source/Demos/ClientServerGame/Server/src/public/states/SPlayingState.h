#pragma once

#include <states/GPlayingState.h>

class SPlayingState : public GPlayingState
{
public:
protected:
private:

public:
	virtual void enter() override;
	virtual std::string update(float i_fDt) override;
	virtual void exit() override;
};