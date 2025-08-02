#pragma once

#include <core/state machine/State.h>

#include <core/Delegates.h>

namespace JNet
{
	class JNetPeer;
	enum JNetPktType;
	struct JNetInPktData;
}

class CConnectingState : public State
{
public:
	Delegate<std::string()> m_unidOnRequestIP;
	Delegate<uint16_t()> m_unidOnRequestPort;
	Delegate<void(const uint8_t i_cuPlayerID)> m_unidOnGameStarted;

protected:
private:
	std::string m_sIp;
	uint16_t m_uPort = 0;
	JNet::JNetPeer* const m_cpClient;
	bool m_bConnected = false;
	std::string m_sNextStateID = "";

public:
	CConnectingState(JNet::JNetPeer* const i_cpClient);

	virtual void enter() override;
	virtual std::string update(float) override;

protected:
private:
	void processGamePkts(JNet::JNetPktType i_PktType, JNet::JNetInPktData& i_rPktData);
};