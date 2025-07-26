#pragma once

#include <iostream>
#include <print>

#include <jNet/JNet.h>

using namespace std;

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

		string sData(maxPacketSizeBytes, '\0');
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

void exampleTwo()
{
	if (!JNet::init()) return;

	print("IP: ");
	string IP;
	cin >> IP;

	print("Port: ");
	u_short port;
	cin >> port;

	const sockaddr_in socAddr = JNet::createAddr(IP, port);
	JNet::bindSocket(socAddr);

	const sockaddr_in destAddr = socAddr;

	sockaddr_in senderAddr;
	int addrLen = sizeof(senderAddr);

	const int maxPacketSizeBytes = 1024;

	while (true)
	{
		print(">> ");
		string in;
		cin >> in;

		JNet::send(in, destAddr);

		string out;
		if (JNet::receive(out))
		{
			println("{}", out);
			if (out == "exit") break;
		}
	}

	JNet::cleanup();
}

int main()
{
	exampleTwo();
	return 0;
}