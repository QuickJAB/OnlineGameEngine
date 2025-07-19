#pragma once

#include <thread>
#include <atomic>

#include <core/game base/GameInstance.h>

class Server;

class SGameInstance : public GameInstance
{
public:
protected:
private:
	Server* const m_cpServer;
	std::thread* const m_cpNetworkThread;

public:
	SGameInstance(std::atomic<bool>& i_rbRunning, Server* const i_cpServer);
	~SGameInstance();

protected:
private:
	static StateMachine* const initStateMachine(Server* const i_cpServer);
};