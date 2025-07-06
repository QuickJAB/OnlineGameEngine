#pragma once

#include <GGameInstance.h>
#include <thread>

class Server;

class SGameInstance : public GGameInstance
{
public:
	SGameInstance();
	~SGameInstance();

	virtual void update(float in_dt) override;

private:
	Server* m_server = nullptr;
	std::thread* networkThread = nullptr;
};