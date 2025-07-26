#include "jNet/JNet.h"

WSAData g_winSocData;
SOCKET g_socket;

bool JNet::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &g_winSocData) != 0) return false;
	g_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	return true;
}

void JNet::cleanup()
{
	closesocket(g_socket);
	WSACleanup();
}

const sockaddr_in JNet::createAddr(const std::string& i_crsIP, const u_short i_cuPort)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(i_cuPort);

	if (i_crsIP == "")
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		inet_pton(AF_INET, i_crsIP.c_str(), &addr.sin_addr);
	}

	return addr;
}

void JNet::bindSocket(const sockaddr_in& i_crAddr)
{
	bind(g_socket, (sockaddr*)&i_crAddr, sizeof(i_crAddr));
	setsockopt(g_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&g_cuReceiveTimeoutTimeMilli, sizeof(g_cuReceiveTimeoutTimeMilli));
}

void JNet::send(const std::string& i_crsData, const sockaddr_in& i_crDestAddr)
{
	sendto(g_socket, i_crsData.c_str(), i_crsData.length(), 0, (sockaddr*)&i_crDestAddr, sizeof(i_crDestAddr));
}

bool JNet::receive(std::string& o_rsData, sockaddr_in& o_rAddr)
{
	o_rsData = std::string(g_cuMaxPacketSize, '\0');
	int iSenderAddrLen = sizeof(sockaddr_in);

	int iPktSize = recvfrom(g_socket, o_rsData.data(), g_cuMaxPacketSize, 0, (sockaddr*)&o_rAddr, &iSenderAddrLen);
	if (iPktSize > 0)
	{
		o_rsData.resize(iPktSize);
		return true;
	}

	return false;
}