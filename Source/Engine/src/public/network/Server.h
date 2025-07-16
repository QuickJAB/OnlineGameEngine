#pragma once

#include <unordered_map>

#include "NetBase.h"

struct ClientTimeOffset
{
	long long llAverage;
	std::queue<long long> qPrevious;
};

class Server : public NetBase
{
public:
protected:
private:
	uint32_t m_uNextPlayerId = 0;
	uint32_t m_uMaxPlayers = 0;

	long long m_llPingDelay = 5000;	// Time in milli
	long long m_llLastPingTime = 0;

	const size_t m_cullMaxOffsets = 10;

	std::unordered_map<uint32_t, ClientTimeOffset> m_umOffsets;

public:
	Server(std::atomic<bool>& i_bRunning, float i_fTickTime, enet_uint16 i_uPort,
		size_t i_ullMaxConnections, enet_uint32 i_uInBandwidth, enet_uint32 i_uOutBandwidth);
	~Server();

	int getNumConnections() const { return static_cast<int>(m_pHost->connectedPeers); }

	int getMaxPlayers() const { return m_uMaxPlayers; }

protected:
	virtual void onConnected(ENetPacket* i_pPacket) override;

private:
	void sendPackets() override;

	void pingClients();
	void updateTimeOffset(std::string i_sData);

	virtual bool shouldQueuePacket(ENetPacket* i_pPacket) override;
};
