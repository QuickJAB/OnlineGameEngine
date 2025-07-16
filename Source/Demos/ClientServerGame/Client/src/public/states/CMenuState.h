#pragma once

#include <core/state machine/State.h>
#include <core/Delegates.h>

class CMenuState : public State
{
public:
protected:
private:
	std::string m_sIpAddress;
	uint16_t m_uPort;

public:
	virtual void enter() override;
	virtual std::string update(float) override;

	std::string getIP() const { return m_sIpAddress; }
	uint16_t getPort() const { return m_uPort; }

protected:
private:
};