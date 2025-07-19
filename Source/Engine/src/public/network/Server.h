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

	const unsigned long long m_cullPingDelay = 5000;
	unsigned long long m_ullLastPingTime = 0;

	const size_t m_cullMaxOffsets = 10;

	std::unordered_map<uint32_t, ClientTimeOffset> m_umOffsets;

public:
	Server(std::atomic<bool>& i_bRunning, const float i_cfTickTime, const HostConfig& i_crHostConfig);
	~Server();

	static ENetAddress* createAddress(const enet_uint16 i_cuPort);

	int getNumConnections() const { return static_cast<int>(m_cpHost->connectedPeers); }

	size_t getMaxPlayers() const { return m_cpHost->peerCount; }

protected:
	virtual void onConnected(const ENetPacket* const i_cpcPacket) override;
	virtual void onDisconnected(const ENetPacket* const i_cpcPacket) override {}

private:
	void sendPackets() override;

	void pingClients();
	void updateTimeOffset(const std::string i_csData);

	virtual bool shouldQueuePacket(const ENetPacket* const i_cpcPacket) override;
};
