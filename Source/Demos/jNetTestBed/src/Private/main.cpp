#pragma once

#include <iostream>
#include <print>
#include <thread>

#include <jNet/JNetPeer.h>
#include <jNet/JNetPackets.h>

void exampleOne()
{
	std::print("IP: ");
	std::string IP;
	std::cin >> IP;

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
		std::print(">> ");
		std::string in;
		std::cin >> in;

		sendto(s, in.c_str(), static_cast<int>(in.length()), 0, (sockaddr*)&addr, sizeof(addr));

		std::string sData(maxPacketSizeBytes, '\0');
		int pktSize = recvfrom(s, sData.data(), maxPacketSizeBytes, 0, (sockaddr*)&senderAddr, &addrLen);
		if (pktSize > 0)
		{
			sData.resize(pktSize);
			std::println("{}", sData);
		}
	}

	closesocket(s);
	WSACleanup();
}

void exampleTwo()
{
	if (!JNet::init()) return;

	std::print("IP: ");
	std::string IP;
	std::cin >> IP;

	std::print("Port: ");
	u_short port;
	std::cin >> port;

	const sockaddr_in socAddr = JNet::createAddr(IP, port);
	JNet::bindSocket(socAddr);

	const sockaddr_in destAddr = socAddr;

	const int maxPacketSizeBytes = 1024;

	std::string in;
	std::string out;
	sockaddr_in senderAddr;

	while (true)
	{
		std::print(">> ");
		std::cin >> in;

		JNet::send(in, destAddr);

		if (JNet::receive(out, senderAddr))
		{
			std::println("{}: {}", inet_ntoa(senderAddr.sin_addr), out);
			if (out == "exit") break;
		}
	}

	JNet::cleanup();
}

void exampleThree()
{
	u_short port = 19;

	JNet::JNetPeer* pServer = new JNet::JNetPeer("127.0.0.1", port, 1, true);
	std::thread t(&JNet::JNetPeer::update, pServer);

	sockaddr_in serverAddr = JNet::createAddr("127.0.0.1", port);

	JNet::RequestConnectPkt pkt;
	std::string pktData = pkt.serialize();
	JNet::send(pktData, serverAddr);
	
	bool running = true;
	std::string in;
	while (running)
	{
		pServer->processIncomingPkts();
	}

	pServer->stop();
	t.join();
	delete pServer;
}

int main()
{
	exampleThree();
	return 0;
}