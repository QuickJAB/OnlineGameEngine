#pragma once

#include "NetBase.h"

class Server : public NetBase
{
public:
	Server(std::atomic<bool>& in_running) : NetBase(in_running) {}
	~Server() = default;

	bool init(float in_tickTime) override;
	void cleanup() override;

private:
	void onReceiveConnection() override;
	void onReceiveDisconnection() override;

	void sendPackets() override;
};
