#include <string>
#include <print>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <thread>

using namespace std;

SOCKET sock;

void listenPkts()
{
	while (true)
	{
		char buffer[512];
		sockaddr_in senderAddr;
		int senderLen = sizeof(senderAddr);
		int received = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&senderAddr, &senderLen);

		if (received > 0)
		{
			println("Received: {}", string(buffer, received));
			break;
		}
	}
}

void sendPkt(const char* data, sockaddr_in& destAddr)
{
	sendto(sock, data, (int)strlen(data), 0, (sockaddr*)&destAddr, sizeof(destAddr));
}

int main()
{
	WSAData wsaData;
	if (int err = WSAStartup(MAKEWORD(2, 2), &wsaData); err != 0)
	{
		println("ERROR: Failed to start WSA with errorcode {}", err);
		return 1;
	}

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	const char* destIP = "127.0.0.1";
	u_short port = 19;

	sockaddr_in localAddr;
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(port);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (sockaddr*)&localAddr, sizeof(localAddr));

	sockaddr_in destAddr;
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(port);
	inet_pton(AF_INET, destIP, &destAddr.sin_addr);

	thread t(listenPkts);

	sendPkt("Test", destAddr);
	
	t.join();

	closesocket(sock);
	WSACleanup();

	return 0;
}