#pragma once

#include <core/state machine/State.h>
#include <network/Server.h>

class Server;

class SWaitingForPlayersState : public State
{
public:
protected:
private:
	Server* const m_cpServer;

public:
	SWaitingForPlayersState(Server* const i_cpServer);

	virtual std::string update(const float) override;

protected:
private:
};