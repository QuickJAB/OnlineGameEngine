#pragma once

#include <mutex>
#include <queue>
#include <NetworkSettings.h>

#include "../extern/enet/include/enet/enet.h"

struct PacketInfo
{
	std::string data;
	int peerIndex;						// Set to -1 to send the packet to all peers
	NetSettings::NetChannel channel;
};

class Server
{
public:
	Server(std::atomic<bool>& in_running) : m_running(in_running) {}
	~Server() = default;

	bool init();
	void update();
	void cleanup();

	void queueOutgoingPacketData(std::string* in_data, int in_peerIndex = -1,
		NetSettings::NetChannel in_channel = NetSettings::NetChannel::unreliable);

private:
	std::atomic<bool>& m_running;
	
	ENetHost* m_host = nullptr;
	ENetAddress m_address;
	ENetEvent m_event;

	std::mutex m_outgoingDataMutex;
	std::queue<PacketInfo> m_outgoingPacketData;

	std::mutex m_incomingDataMutex;
	std::queue<ENetPacket*> m_incomingPacketData;

	void onClientConnected();
	void onReceivePacket();
	void onClientDisconnected();

	void sendPackets();

	void queueIncomingPacketData(ENetPacket* in_packet);
};

