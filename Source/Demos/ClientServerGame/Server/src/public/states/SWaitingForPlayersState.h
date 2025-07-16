#pragma once

#include <core/state machine/State.h>
#include <network/Server.h>

class Server;

class SWaitingForPlayersState : public State
{
public:
protected:
private:
	Server* m_pServer = nullptr;

public:
	SWaitingForPlayersState(Server* i_pServer);

	virtual std::string update(float) override;

protected:
private:
};