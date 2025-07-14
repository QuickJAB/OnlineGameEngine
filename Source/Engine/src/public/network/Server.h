#pragma once

#include "NetBase.h"

class Server : public NetBase
{
public:
	Server(std::atomic<bool>& in_running, float in_tickTime, enet_uint16 in_port,
		size_t in_maxConnections, enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth);
	~Server();

	int getNumConnections() const { return static_cast<int>(m_host->connectedPeers); }

	int getMaxPlayers() const { return m_maxPlayers; }

private:
	void sendPackets() override;

	void pingClients();
	void updateTimOffset(std::string in_data);

	virtual bool shouldQueuePacket(ENetPacket* in_packet) override;

	uint32_t m_maxPlayers = 0;

	long long m_pingDelay = 5000.f;	// Time in milli
	long long m_lastPingTime = 0.f;

	const uint8_t m_MAX_PING_COUNT = 10;
};
