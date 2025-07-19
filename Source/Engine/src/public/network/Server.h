#pragma once

#include <unordered_map>

#include "NetBase.h"

struct ClientTimeOffset
{
	unsigned long long ullAverage;
	std::queue<unsigned long long> qPrevious;
};

class Server : public NetBase
{
public:
protected:
private:
	uint32_t m_uNextPlayerId = 0;
	const uint32_t m_cuMaxPlayers;

	const unsigned long long m_cullPingDelay = 5000;
	unsigned long long m_ullLastPingTime = 0;

	const size_t m_cullMaxOffsets = 10;

	std::unordered_map<uint32_t, ClientTimeOffset> m_umOffsets;

public:
	Server(std::atomic<bool>& i_bRunning, const float i_cfTickTime, const enet_uint16 i_cuPort,
		const size_t i_cullMaxConnections, const enet_uint32 i_cuInBandwidth, const enet_uint32 i_cuOutBandwidth);
	~Server();

	int getNumConnections() const { return static_cast<int>(m_cpHost->connectedPeers); }

	int getMaxPlayers() const { return m_cuMaxPlayers; }

protected:
	virtual void onConnected(const ENetPacket* const i_cpcPacket) override;
	virtual void onDisconnected(const ENetPacket* const i_cpcPacket) override {}

private:
	void sendPackets() override;

	void pingClients();
	void updateTimeOffset(const std::string i_csData);

	virtual bool shouldQueuePacket(const ENetPacket* const i_cpcPacket) override;

	static ENetAddress* createAddress(const enet_uint16 i_cuPort);
};
