#pragma once

#include <core/state machine/State.h>
#include <core/Delegates.h>

class CMenuState : public State
{
public:
	virtual void enter() override;
	virtual std::string update(float) override;

	std::string getIP() const { return m_ipAddress; }
	uint16_t getPort() const { return m_port; }

private:
	std::string m_ipAddress;
	uint16_t m_port;
};