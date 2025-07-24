#pragma once

#include <unordered_map>
#include <queue>
#include <mutex>
#include <atomic>
#include <WinSock2.h>
#include <Ws2tcpip.h>

namespace JNet
{
	inline constexpr uint32_t g_ucMaxPacketSizeBytes = 100;

	static class JNetBase
	{
	public:
	protected:
	private:
		static WSAData s_WSAData;
		static SOCKET s_socket;

		static std::unordered_map<uint32_t, sockaddr_in> s_umConnections;

		inline static uint32_t s_uNextConnectionID = 0;

		static std::queue<char[g_ucMaxPacketSizeBytes]> s_qIncoming;
		static std::mutex s_mutIncoming;

		static std::queue<char[g_ucMaxPacketSizeBytes]> s_qOutgoing;
		static std::mutex s_mutOutgoing;

		static std::atomic<bool>& s_bRunning;
		inline static bool s_bHasInit = false;

	public:
		static void init(std::atomic<bool>& i_bRunning);
	protected:
	private:
		static void update();
	};
}