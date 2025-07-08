#pragma once

#include <string>
#include <mutex>
#include <queue>
#include <enet/enet.h>

struct PacketInfo
{
	std::string data;
	int peerIndex;
};

class NetBase
{
public:
	NetBase(std::atomic<bool>& in_running, float in_tickTime);
	~NetBase();

	virtual void update();

	virtual void queueOutgoingPacketData(std::string in_data, int in_peerIndex = -1);

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

	void queueIncomingPacketData(ENetPacket* in_packet);

	virtual void onReceiveConnection();

	virtual bool shouldQueuePacket(ENetPacket* in_packet);
	
	virtual void onReceiveDisconnection();

	virtual void sendPackets();

private:
	void onReceivePacket();
};
