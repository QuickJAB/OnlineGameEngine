#pragma once

#include <states/GPlayingState.h>

namespace JNet
{
	class JNetPeer;
	struct JNetInPktData;
	enum JNetPktType;
}

class SPlayingState : public GPlayingState
{
public:
protected:
private:
	float m_fTickAcum = 0.f;
	const float m_cfTickRateMilli = 50; // 20 ticks per second

public:
	SPlayingState(JNet::JNetPeer* const i_cpServer);
	~SPlayingState() = default;

	void enter() override;
	std::string update(const float i_cfDt) override;
	void exit() override;

protected:
private:
	void processIncomingPkts(JNet::JNetPktType i_pktType, JNet::JNetInPktData& i_rPktData);
};