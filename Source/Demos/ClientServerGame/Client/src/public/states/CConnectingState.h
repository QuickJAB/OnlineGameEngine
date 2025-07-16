#pragma once

#include <core/state machine/State.h>
#include <network/Client.h>

#include <core/Delegates.h>

class CConnectingState : public State
{
public:
	Delegate<std::string()> m_unidOnRequestIP;
	Delegate<uint16_t()> m_unidOnRequestPort;
	Delegate<Client* ()> m_unidOnRequestClient;
	Delegate<void()> m_unidOnConnectionEstablished;
	Delegate<void(long long)> m_unidOnGameStarted;

protected:
private:
	std::string m_sIp;
	uint16_t m_uPort = 0;
	Client* m_pClient = nullptr;
	bool m_bConnected = false;

public:
	virtual void enter() override;
	virtual std::string update(float) override;

protected:
private:
	void startGame(const char* i_cpData);
};