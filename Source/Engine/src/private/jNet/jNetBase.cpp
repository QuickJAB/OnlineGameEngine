#include "jNet/jNetBase.h"

using namespace JNet;

bool JNetBase::init(std::atomic<bool>& i_bRunning)
{
	if (s_bHasInit) return true;
	
	if (int iErr = WSAStartup(MAKEWORD(2, 2), &s_WSAData); iErr > 0)
	{
		return false;
	}

	s_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	s_localAddr.sin_family = AF_INET;
	s_localAddr.sin_port = htons(g_cuPort);

	s_bRunning.exchange(i_bRunning);

	s_bHasInit = true;

	return true;
}

void JNetBase::initLocalAddr(const char* const i_cpcchDestIP)
{
	if (i_cpcchDestIP != nullptr)
	{
		inet_pton(AF_INET, i_cpcchDestIP, &s_localAddr.sin_addr);
	}
	else
	{
		s_localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	bind(s_socket, (sockaddr*)&s_localAddr, sizeof(s_localAddr));

	s_bIsSocketBound = true;
}

void JNetBase::update()
{
	int iSenderLen = -1;
	IncomingData data;

	while (s_bRunning.load())
	{
		if (!s_bIsSocketBound || recvfrom(s_socket, data.chaData, g_cuMaxPacketSizeBytes, 0, (sockaddr*)&data.senderAddr, &iSenderLen) <= 0)
		{
			continue;
		}

		s_mutIncoming.lock();
		s_qIncoming.push(data);
		s_mutIncoming.unlock();

		sendNextPacket();
	}

	cleanup();
}

void JNetBase::addConnection(const char* const i_cpcchIP)
{
	sockaddr_in destAddr;
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(g_cuPort);
	inet_pton(AF_INET, i_cpcchIP, &destAddr.sin_addr);

	s_umConnections.insert(std::pair<uint32_t, sockaddr_in>(s_uNextConnectionID, destAddr));

	++s_uNextConnectionID;
}

void JNetBase::queuePacket(const OutgoingData& i_crOutgoingData)
{
	s_mutOutgoing.lock();
	s_qOutgoing.push(i_crOutgoingData);
	s_mutOutgoing.unlock();
}

void JNetBase::sendNextPacket()
{
	s_mutOutgoing.lock();

	if (s_qOutgoing.empty())
	{
		s_mutOutgoing.unlock();
		return;
	}

	OutgoingData packetData = s_qOutgoing.front();
	s_qOutgoing.pop();

	s_mutOutgoing.unlock();

	sendPacket(packetData);
	delete packetData.pchData;
}

void JNetBase::sendPacket(const OutgoingData& cPacketData)
{
	sockaddr_in pDestAddr = s_umConnections[cPacketData.uDest];

	sendto(s_socket, cPacketData.pchData, cPacketData.iLength, 0, (sockaddr*)&pDestAddr, sizeof(pDestAddr));
}

void JNetBase::cleanup()
{
	s_mutIncoming.lock();
	IncomingData inData;
	for (int i = 0; i < s_qIncoming.size(); ++i)
	{
		inData = s_qIncoming.front();
		s_qIncoming.pop();
		delete inData.chaData;
	}
	s_mutIncoming.unlock();

	s_mutOutgoing.lock();
	OutgoingData outData;
	for (int i = 0; i < s_qIncoming.size(); ++i)
	{
		outData = s_qOutgoing.front();
		s_qOutgoing.pop();
		delete outData.pchData;
	}
	s_mutOutgoing.unlock();

	closesocket(s_socket);
	WSACleanup();
}
