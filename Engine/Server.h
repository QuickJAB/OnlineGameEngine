#pragma once

#include <mutex>
#include <queue>

#include "../extern/enet/include/enet/enet.h"

// Net channels are per-peer and should be used too logically separate out data flows
enum NetChannel
{
	unreliable,
	reliable,
	size
};

struct PacketInfo
{
	std::string data;
	int peerIndex;			// Set to -1 to send the packet to all peers
	NetChannel channel;
};

class Server
{
public:
	Server() = default;
	~Server() = default;

	bool init();
	void update(bool& in_running);
	void cleanup();

	void queueOutgoingPacketData(std::string* in_data, int in_peerIndex = -1,
		NetChannel in_channel = NetChannel::unreliable);

private:
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

