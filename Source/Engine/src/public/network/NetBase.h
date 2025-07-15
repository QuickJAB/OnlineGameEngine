#pragma once

#include <string>
#include <mutex>
#include <queue>
#include <enet/enet.h>

#include "core/Delegates.h"

struct PacketInfo
{
	std::string data;
	int peerIndex;
};

enum ServerCommand
{
	handshake,
	ping
};

enum ClientCommand
{
	pong
};

class NetBase
{
public:
	NetBase(std::atomic<bool>& in_running, float in_tickTime);
	~NetBase();

	void update();

	virtual void queueOutgoingPacketData(std::string in_data, int in_peerIndex = -1);

	std::queue<ENetPacket> getIncomingPacketData();

	long long getClockTime();

protected:
	std::atomic<bool>& m_running;
	float m_tickTime = 0.f;

	ENetHost* m_host = nullptr;
	ENetAddress m_address = ENetAddress();
	ENetEvent m_event = ENetEvent();

	std::mutex m_outgoingDataMutex;
	std::queue<PacketInfo> m_outgoingPacketData;

	std::mutex m_incomingDataMutex;
	std::queue<ENetPacket> m_incomingPacketData;

	MulticastDelegate<void()> onNetUpdate;

	virtual bool shouldQueuePacket(ENetPacket* in_packet);

	virtual void sendPackets();

	virtual void onConnected(ENetPacket* in_packet);

	virtual void onDisconnected(ENetPacket* in_packet);

private:
	void queueIncomingPacketData(ENetPacket* in_packet);
};
