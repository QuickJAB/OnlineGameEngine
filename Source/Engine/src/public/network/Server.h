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

	uint32_t m_maxPlayers = 0;
};
