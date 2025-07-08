#pragma once

#include <core/state machine/State.h>
#include <network/Client.h>

#include <core/Delegates.h>

class CConnectingState : public State
{
public:
	virtual void enter() override;
	virtual std::string update(float) override;

	Delegate<std::string()> onRequestIP;
	Delegate<uint16_t()> onRequestPort;
	Delegate<Client*()> onRequestClient;

private:
	std::string m_ip;
	uint16_t m_port;
	Client* m_client;
	bool m_connected = false;
};