#pragma once

#include <core/state machine/State.h>
#include <network/Client.h>

#include <core/Delegates.h>

class CConnectingState : public State
{
public:
	Delegate<std::string()> m_unidOnRequestIP;
	Delegate<uint16_t()> m_unidOnRequestPort;
	Delegate<void()> m_unidOnGameStarted;

protected:
private:
	std::string m_sIp;
	uint16_t m_uPort = 0;
	Client* const m_cpClient;
	bool m_bConnected = false;

public:
	CConnectingState(Client* const i_cpClient);

	virtual void enter() override;
	virtual std::string update(float) override;

protected:
private:
	void startGame(const char* i_cpData);
};