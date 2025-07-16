#pragma once

#include <thread>

#include <core/game base/GameInstance.h>

class Server;

class SGameInstance : public GameInstance
{
public:
protected:
private:
	Server* m_pServer = nullptr;
	std::thread* m_pNetworkThread = nullptr;

public:
	SGameInstance();
	~SGameInstance();

protected:
private:
};