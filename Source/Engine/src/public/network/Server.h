#pragma once

#include <unordered_map>

#include "NetBase.h"

struct ClientTimeOffset
{
	long long average;
	std::queue<long long> previous;
};

class Server : public NetBase
{
public:
	Server(std::atomic<bool>& in_running, float in_tickTime, enet_uint16 in_port,
		size_t in_maxConnections, enet_uint32 in_inBandwidth, enet_uint32 in_outBandwidth);
	~Server();

	int getNumConnections() const { return static_cast<int>(m_host->connectedPeers); }

	int getMaxPlayers() const { return m_maxPlayers; }

protected:
	virtual void onConnected(ENetPacket* in_packet) override;

private:
	void sendPackets() override;

	void pingClients();
	void updateTimeOffset(std::string in_data);

	virtual bool shouldQueuePacket(ENetPacket* in_packet) override;

	uint32_t m_nextPlayerId = 0;
	uint32_t m_maxPlayers = 0;

	long long m_pingDelay = 5000.f;	// Time in milli
	long long m_lastPingTime = 0.f;

	const size_t m_MAX_OFFSETS = 10;
	std::unordered_map<uint32_t, ClientTimeOffset> m_offsets;
};
