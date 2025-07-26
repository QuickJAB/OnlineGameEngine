#include "jNet/jNetBase.h"

#include <string>

#include "core/Serializer.h"
#include "jNet/jNetPkts.h"

using namespace JNet;
using namespace std;

bool JNetBase::init(atomic<bool>& i_bRunning)
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

void JNetBase::initLocalAddr(const string* const i_cpcsDestIP)
{
	if (i_cpcsDestIP != nullptr)
	{
		inet_pton(AF_INET, i_cpcsDestIP->c_str(), &s_localAddr.sin_addr);
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
		if (!s_bIsSocketBound ||
			recvfrom(s_socket, data.sData.data(), g_cuMaxPacketSizeBytes, 0, (sockaddr*)&data.senderAddr, &iSenderLen) <= 0)
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

const uint32_t JNetBase::addConnection(const string i_csIP)
{
	for (const pair<uint32_t, sockaddr_in>& pair : s_umConnections)
	{
		string sIP;
		inet_ntop(AF_INET, &(pair.second.sin_addr), sIP.data(), g_cuAddrLen);
		if (sIP == i_csIP)
		{
			return pair.first;
		}
	}

	sockaddr_in destAddr;
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(g_cuPort);
	inet_pton(AF_INET, i_csIP.data(), &destAddr.sin_addr);

	const uint32_t cuNewConnectionID = s_uNextConnectionID;
	++s_uNextConnectionID;
	s_umConnections.insert(pair<uint32_t, sockaddr_in>(cuNewConnectionID, destAddr));

	return cuNewConnectionID;
}

void JNetBase::queuePacket(const OutgoingData& i_crOutgoingData)
{
	s_mutOutgoing.lock();
	s_qOutgoing.push(i_crOutgoingData);
	s_mutOutgoing.unlock();
}

queue<IncomingData> JNetBase::getQueuedPackets()
{
	s_mutIncoming.lock();
	queue<IncomingData> qPktData = s_qIncoming;

	for (size_t i = 0; i < s_qIncoming.size(); ++i)
	{
		s_qIncoming.pop();
	}
	s_mutIncoming.unlock();

	return qPktData;
}

void JNetBase::processIncomingPackets()
{
	queue<IncomingData> qPktData = getQueuedPackets();
	
	while (!qPktData.empty())
	{
		const IncomingData cPktData = qPktData.front();
		string sData = cPktData.sData;
		const PktType cuPktType = BinarySerializer::deserialize<PktType>(sData);

		switch (cuPktType)
		{
		case RequestConnect:
			onConnectionRequested(cPktData.senderAddr);
			break;

		case AcceptConnect:
			s_uLocalID = BinarySerializer::deserialize<uint32_t>(sData);
			break;

		case Ping:
			break;

		case Pong:
			break;
		}
	}
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
}

void JNetBase::sendPacket(const OutgoingData& cPacketData)
{
	sockaddr_in pDestAddr = s_umConnections[cPacketData.uDest];

	sendto(s_socket, cPacketData.sData.c_str(), cPacketData.iLength, 0, (sockaddr*)&pDestAddr, sizeof(pDestAddr));
}

void JNetBase::cleanup()
{
	s_mutIncoming.lock();
	IncomingData inData;
	for (int i = 0; i < s_qIncoming.size(); ++i)
	{
		inData = s_qIncoming.front();
		s_qIncoming.pop();
	}
	s_mutIncoming.unlock();

	s_mutOutgoing.lock();
	OutgoingData outData;
	for (int i = 0; i < s_qIncoming.size(); ++i)
	{
		outData = s_qOutgoing.front();
		s_qOutgoing.pop();
	}
	s_mutOutgoing.unlock();

	closesocket(s_socket);
	WSACleanup();
}

void JNetBase::onConnectionRequested(const sockaddr_in& i_cAddr)
{
	string sIP;
	inet_ntop(AF_INET, &(i_cAddr.sin_addr), sIP.data(), g_cuAddrLen);

	ServerAcceptConnectPkt pkt;
	pkt.uClientID = addConnection(sIP);
	
	OutgoingData pktData;
	pktData.uDest = pkt.uClientID;
	pktData.sData = pkt.serialize();
	pktData.iLength = sizeof(pktData.sData);

	queuePacket(pktData);
}
