#pragma once

#include <thread>

#include <core/game base/GameInstance.h>

class Server;

class SGameInstance : public GameInstance
{
public:
	SGameInstance();
	~SGameInstance();

private:
	Server* m_server = nullptr;
	std::thread* networkThread = nullptr;
};