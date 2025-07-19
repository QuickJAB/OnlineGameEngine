#pragma once

#include <states/GPlayingState.h>

class SPlayingState : public GPlayingState
{
public:
protected:
private:

public:
	SPlayingState();
	~SPlayingState() = default;

	virtual void enter() override;
	virtual std::string update(const float i_cfDt) override;
	virtual void exit() override;

protected:
private:
};