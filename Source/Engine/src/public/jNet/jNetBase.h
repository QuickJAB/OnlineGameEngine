#pragma once

#include <unordered_map>
#include <queue>
#include <mutex>
#include <atomic>
#include <WinSock2.h>
#include <Ws2tcpip.h>

namespace JNet
{
	inline constexpr uint32_t g_cuMaxPacketSizeBytes = 100;
	inline constexpr u_short g_cuPort = 19;
	inline constexpr u_short g_cuAddrLen = 15;

	struct IncomingData
	{
		sockaddr_in senderAddr;
		char chaData[g_cuMaxPacketSizeBytes];
	};

	struct OutgoingData
	{
		uint32_t uDest;
		char* pchData;
		int iLength;
	};

	class JNetBase
	{
	public:
	protected:
	private:
		static WSAData s_WSAData;
		static SOCKET s_socket;

		static sockaddr_in s_localAddr;
		static std::unordered_map<uint32_t, sockaddr_in> s_umConnections;

		inline static uint32_t s_uNextConnectionID = 0;
		inline static uint32_t s_uLocalID = (uint32_t)-1;

		static std::queue<IncomingData> s_qIncoming;
		static std::mutex s_mutIncoming;

		static std::queue<OutgoingData> s_qOutgoing;
		static std::mutex s_mutOutgoing;

		static std::atomic<bool>& s_bRunning;
		inline static bool s_bHasInit = false;
		inline static bool s_bIsSocketBound = false;

	public:
		static bool init(std::atomic<bool>& i_bRunning);
		static void initLocalAddr(const char* const i_cpcchDestIP = nullptr);
		static void update();
		static void addConnection(const char* const i_cpcchIP);
		static void queuePacket(const OutgoingData& i_crOutgoingData);
		static std::queue<IncomingData> getQueuedPackets();
		static void processIncomingPackets();

	protected:
	private:
		static void sendNextPacket();
		static void sendPacket(const OutgoingData& cPacketData);
		static void cleanup();
		static void onPingReceived();
	};
}