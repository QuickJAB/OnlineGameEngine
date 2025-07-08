#pragma once

#include <core/state machine/State.h>
#include <core/Delegates.h>

class CMenuState : public State
{
public:
	virtual void enter() override;
	virtual std::string update(float) override;

	Delegate<void(std::string, uint16_t)> onConnectionDetailsSet;

private:
	std::string m_ipAddress;
	uint16_t m_port;
};