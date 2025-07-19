#pragma once

#include <thread>
#include <functional>

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
	SGameInstance();
	~SGameInstance();

protected:
private:
	static Server* const initServer(std::atomic<bool>& i_bRunning);
	static StateMachine* const initStateMachine(Server* const i_cpServer);
};