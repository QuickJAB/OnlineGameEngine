#include "jNet/jNetBase.h"

using namespace JNet;

void JNetBase::init(std::atomic<bool>& i_bRunning)
{
	if (s_bHasInit) return;
	
	if (int iErr = WSAStartup(MAKEWORD(2, 2), &s_WSAData); iErr > 0)
	{
		return;
	}

	s_bHasInit = true;
	s_bRunning.exchange(i_bRunning);
}

void JNetBase::update()
{
	char chaData[g_ucMaxPacketSizeBytes];
	sockaddr_in senderAddress;
	int iSenderLen;

	while (s_bRunning.load())
	{
		if (recvfrom(s_socket, chaData, g_ucMaxPacketSizeBytes, 0, (sockaddr*)&senderAddress, &iSenderLen) > 0)
		{
			s_mutIncoming.lock();
			s_qIncoming.push(chaData);
			s_mutOutgoing.unlock();
		}
	}
}