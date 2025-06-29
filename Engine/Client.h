#pragma once

#include "NetBase.h"

class Client : public NetBase
{
public:
	Client(std::atomic<bool>& in_running) : NetBase(in_running) {}
	~Client() = default;

	bool init(float in_tickTime) override;
	void cleanup() override;

	bool tryConnect(std::string in_ip, uint32_t in_attemptLength = 30);

private:
	ENetPeer* m_peer = nullptr;

	void onReceiveConnection() override;
	void onReceiveDisconnection() override;

	void sendPackets() override;
};

