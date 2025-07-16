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
	Client(std::atomic<bool>& i_bRunning, float i_fTickTime, enet_uint32 i_uInBandwidth, enet_uint32 i_uOutBandwidth);
	~Client();

	bool tryConnect(std::string i_sIp, enet_uint16 i_uPort, uint32_t i_uAttemptLength = 30);

protected:
private:
	void sendPackets() override;

	void processHandshake(std::string i_sData);

	void pongServer(std::string i_sPingData);

	virtual bool shouldQueuePacket(ENetPacket* i_pPacket) override;
};

