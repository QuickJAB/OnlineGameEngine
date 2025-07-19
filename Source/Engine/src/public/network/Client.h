#pragma once

#include "NetBase.h"

class Client : public NetBase
{
public:
protected:
private:
	ENetPeer* m_pPeer = nullptr;

	uint32_t m_uPlayerId = 0;

public:
	Client(std::atomic<bool>& i_bRunning, const float i_cfTickTime,
		const enet_uint32 i_cuInBandwidth, const enet_uint32 i_cuOutBandwidth);
	~Client();

	bool tryConnect(const std::string i_csIp, const enet_uint16 i_cuPort,
		const uint32_t i_cuAttemptLength = 30);

	uint32_t getNetworkId() const { return m_uPlayerId; }

protected:
private:
	void sendPackets() override;

	void processHandshake(const std::string i_csData);

	void pongServer(const std::string i_csPingData);

	virtual bool shouldQueuePacket(const ENetPacket* i_cpPacket) override;
};

