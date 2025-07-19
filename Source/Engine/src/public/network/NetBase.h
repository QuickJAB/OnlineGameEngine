#pragma once

#include <string>
#include <mutex>
#include <queue>
#include <enet/enet.h>

#include "core/Delegates.h"

struct PacketInfo
{
	std::string sData;
	int iPeerIndex;
};

enum ServerCommand
{
	handshake,
	ping,
	startGame,
	gameState,
	endGame
};

enum ClientCommand
{
	pong,
	inputState
};

class NetBase
{
public:
protected:
	std::atomic<bool>& m_bRunning;
	const float m_cfTickTime = 0.f;

	ENetHost* m_pHost = nullptr;
	ENetAddress m_Address = ENetAddress();
	ENetEvent m_Event = ENetEvent();

	std::mutex m_OutgoingDataMutex;
	std::queue<PacketInfo> m_qOutgoingPacketData;

	std::mutex m_IncomingDataMutex;
	std::queue<ENetPacket> m_qIncomingPacketData;

	MulticastDelegate<void()> m_muldOnNetUpdate;

private:

public:
	NetBase(std::atomic<bool>& i_bRunning, const float i_cfTickTime);
	~NetBase();

	void update();

	virtual void queueOutgoingPacketData(const std::string i_csData, const int i_ciPeerIndex = -1);

	std::queue<ENetPacket> getIncomingPacketData();

	long long getClockTime();

protected:
	virtual bool shouldQueuePacket(const ENetPacket* const i_cpcPacket);

	virtual void sendPackets();

	virtual void onConnected(const ENetPacket* const i_cpcPacket);

	virtual void onDisconnected(const ENetPacket* const i_cpcPacket);

private:
	void queueIncomingPacketData(const ENetPacket* const i_cpcPacket);
};
