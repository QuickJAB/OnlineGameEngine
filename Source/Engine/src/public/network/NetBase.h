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

struct HostConfig
{
	const ENetAddress* pcAddress = nullptr;
	size_t ullMaxConnections = 1;
	size_t ullMaxChannels = 1;
	enet_uint32 uInBadnwidth = 0;	// 0 is uncapped
	enet_uint32 uOutBandwidth = 0;	// 0 is uncapped
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

	ENetHost* const m_cpHost;
	ENetEvent m_Event = ENetEvent();

	std::mutex m_OutgoingDataMutex;
	std::queue<PacketInfo> m_qOutgoingPacketData;

	std::mutex m_IncomingDataMutex;
	std::queue<ENetPacket> m_qIncomingPacketData;

	MulticastDelegate<void()> m_muldOnNetUpdate;

private:

public:
	NetBase(std::atomic<bool>& i_bRunning, const float i_cfTickTime, const HostConfig& i_crHostConfig);
	~NetBase();

	void update();

	virtual void queueOutgoingPacketData(const std::string i_csData, const int i_ciPeerIndex = -1);

	std::queue<ENetPacket> getIncomingPacketData();

	long long getClockTime();

protected:
	virtual bool shouldQueuePacket(const ENetPacket* const i_cpcPacket) = 0;
	virtual void sendPackets() = 0;
	virtual void onConnected(const ENetPacket* const i_cpcPacket) = 0;
	virtual void onDisconnected(const ENetPacket* const i_cpcPacket) = 0;

private:
	void queueIncomingPacketData(const ENetPacket* const i_cpcPacket);

	static ENetHost* const initAndCreateHost(const HostConfig& i_crHostConfig);
};
