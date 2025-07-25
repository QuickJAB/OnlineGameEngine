#pragma once

#include "NetBase.h"

class Client : public NetBase
{
public:
protected:
private:
	ENetPeer* m_pPeer = nullptr;

	uint32_t m_uPlayerId = 0;

	bool m_bConnected = false;
	const float m_cfMaxConnectingTime = 5000.f;

public:
	Client(std::atomic<bool>& i_bRunning, const float i_cfTickTime, const HostConfig& i_crHostConfig);
	~Client();

	bool tryConnect(const std::string i_csIp, const enet_uint16 i_cuPort);

	uint32_t getNetworkId() const { return m_uPlayerId; }

protected:
private:
	void sendPackets() override;

	void processHandshake(const std::string i_csData);

	void pongServer(const std::string i_csPingData);

	virtual bool shouldQueuePacket(const ENetPacket* const i_cpcPacket) override;

	virtual void onConnected(const ENetPacket* const i_cpcPacket) override;
	virtual void onDisconnected(const ENetPacket* const i_cpcPacket) override {}
};

