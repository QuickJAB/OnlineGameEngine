#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace JNet
{
	inline static constexpr uint16_t g_cuMaxPacketSize = 1024;
	inline static constexpr uint32_t g_cuReceiveTimeoutTimeMilli = 1;

	bool init();
	void cleanup();
	const sockaddr_in createAddr(const std::string& i_crsIP, const u_short i_cuPort);
	void bindSocket(const sockaddr_in& i_crAddr);
	void send(const std::string& i_crsData, const sockaddr_in& i_crDestAddr);
	bool receive(std::string& o_rsData, std::string& o_rsSenderIP);
}