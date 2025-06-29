#pragma once

#include <string>
#include <mutex>
#include <queue>
#include "../extern/enet/include/enet/enet.h"

#include "NetworkSettings.h"

struct PacketInfo
{
	std::string data;
	int peerIndex;						// Set to -1 to send the packet to all peers
	NetSettings::NetChannel channel;
};

class NetBase
{
public:
	NetBase(std::atomic<bool>& in_running) : m_running(in_running) {}
	~NetBase() = default;

	virtual bool init(float in_tickTime);
	virtual void update();
	virtual void cleanup();

	virtual void queueOutgoingPacketData(std::string* in_data, int in_peerIndex = -1,
		NetSettings::NetChannel in_channel = NetSettings::NetChannel::unreliable);

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

	virtual void queueIncomingPacketData(ENetPacket* in_packet);

	virtual void onReceiveConnection();
	virtual void onReceivePacket();
	virtual void onReceiveDisconnection();

	virtual void sendPackets() {}
};
