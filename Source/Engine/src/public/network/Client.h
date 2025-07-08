#pragma once

#include "NetBase.h"

class Client : public NetBase
{
public:
	Client(std::atomic<bool>& in_running, float in_tickTime, enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth);
	~Client();

	bool tryConnect(std::string in_ip, enet_uint16 in_port, uint32_t in_attemptLength = 30);

private:
	ENetPeer* m_peer = nullptr;

	void sendPackets() override;
};

