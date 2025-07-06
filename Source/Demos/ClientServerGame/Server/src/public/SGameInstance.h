#pragma once

#include <GGameInstance.h>
#include <thread>

class Server;

class SGameInstance : public GGameInstance
{
public:
	SGameInstance();
	~SGameInstance();

private:
	Server* m_server = nullptr;
	std::thread* networkThread = nullptr;
};