#pragma once

#include <unordered_map>
#include <queue>
#include <mutex>
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
		std::string sData;
	};

	struct OutgoingData
	{
		uint32_t uDest;
		std::string sData;
		int iLength;
	};

	class JNetBase
	{
	public:
	protected:
	private:
		inline static WSAData s_WSAData = WSAData();
		inline static SOCKET s_socket = SOCKET();

		inline static sockaddr_in s_localAddr = sockaddr_in();
		inline static std::unordered_map<uint32_t, sockaddr_in> s_umConnections = std::unordered_map<uint32_t, sockaddr_in>();

		inline static uint32_t s_uNextConnectionID = 0;
		inline static uint32_t s_uLocalID = UINT32_MAX;

		inline static std::queue<IncomingData> s_qIncoming = std::queue<IncomingData>();
		inline static std::mutex s_mutIncoming = std::mutex();

		inline static std::queue<OutgoingData> s_qOutgoing = std::queue<OutgoingData>();
		inline static std::mutex s_mutOutgoing = std::mutex();

		inline static bool s_bHasInit = false;
		inline static bool s_bIsSocketBound = false;

	public:
		static const uint32_t getLocalID() { return s_uLocalID; }

		static bool init();
		static void initLocalAddr(const std::string* const i_cpcsDestIP = nullptr);
		static void update();
		static const uint32_t addConnection(const std::string i_csIP);
		static void queuePacket(const OutgoingData& i_crOutgoingData);
		static std::queue<IncomingData> getQueuedPackets();
		static void processIncomingPackets();
		static void stopNetThread();

	protected:
	private:
		static void sendNextPacket();
		static void sendPacket(const OutgoingData& cPacketData);
		static void cleanup();
		static void onConnectionRequested(const sockaddr_in& i_cAddr);
	};
}