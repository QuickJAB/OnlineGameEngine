#pragma once

#include <thread>
#include <iostream>
#include <string>
#include <print>

#include <jNet/jNetBase.h>
#include <jNet/jNetPkts.h>

using namespace std;
using namespace JNet;

void exampleOne()
{
	print("IP: ");
	string IP;
	cin >> IP;

	WSAData data;
	SOCKET s;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return;
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(19);
	inet_pton(AF_INET, IP.c_str(), &addr.sin_addr);
	bind(s, (sockaddr*)&addr, sizeof(addr));

	sockaddr_in senderAddr;
	int addrLen = sizeof(senderAddr);

	const int maxPacketSizeBytes = 1024;

	while (true)
	{
		print(">> ");
		string in;
		cin >> in;

		sendto(s, in.c_str(), in.length(), 0, (sockaddr*)&addr, sizeof(addr));

		string sData(g_cuMaxPacketSizeBytes, '\0');
		int pktSize = recvfrom(s, sData.data(), maxPacketSizeBytes, 0, (sockaddr*)&senderAddr, &addrLen);
		if (pktSize > 0)
		{
			sData.resize(pktSize);
			println("{}", sData);
		}
	}

	closesocket(s);
	WSACleanup();
}

int main()
{
	exampleOne();
	return 0;
}