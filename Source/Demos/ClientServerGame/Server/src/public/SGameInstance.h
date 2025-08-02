#pragma once

#include <atomic>

#include <core/game base/GameInstance.h>

namespace JNet
{
	class JNetPeer;
}

class SGameInstance : public GameInstance
{
public:
protected:
private:
	JNet::JNetPeer* const m_cpServer;

public:
	SGameInstance(std::atomic<bool>& i_rbRunning, JNet::JNetPeer* const i_cpServer);
	~SGameInstance();

protected:
private:
	static StateMachine* const initStateMachine(JNet::JNetPeer* const i_cpServer);
};