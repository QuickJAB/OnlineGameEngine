#pragma once

#include <core/state machine/State.h>

namespace JNet
{
	class JNetPeer;
}

class SWaitingForPlayersState : public State
{
public:
protected:
private:
	JNet::JNetPeer* const m_cpServer;

public:
	SWaitingForPlayersState(JNet::JNetPeer* const i_cpServer);

	virtual void enter() override;
	virtual std::string update(const float) override;

protected:
private:
};