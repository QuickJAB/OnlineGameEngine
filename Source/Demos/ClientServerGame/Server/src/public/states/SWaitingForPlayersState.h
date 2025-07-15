#pragma once

#include <core/state machine/State.h>
#include <network/Server.h>

class Server;

class SWaitingForPlayersState : public State
{
public:
	SWaitingForPlayersState(Server* in_server);

	virtual std::string update(float) override;

private:
	Server* m_server = nullptr;
};