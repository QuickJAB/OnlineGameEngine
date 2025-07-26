#pragma once

#include <queue>
#include <mutex>
#include <unordered_map>

#include "JNet.h"

namespace JNet
{
	struct JNetInPktData
	{
		std::string sData;
		std::string sIP;
	};

	struct JNetOutPktData
	{
		std::string sData;
		int iDestID = -1;
	};

	class JNetPeer
	{
	public:
	protected:
	private:
		bool m_bRunning;

		std::queue<JNetInPktData> m_qInPkts;
		std::mutex m_mutInPkts;

		std::queue<JNetOutPktData> m_qOutPkts;
		std::mutex m_mutOutPkts;

		uint8_t m_uNextConnectionID = 0;
		std::unordered_map<uint8_t, sockaddr_in> m_umConnections;

	public:
		JNetPeer(const u_short i_cuPort);
		~JNetPeer();

		void update();
		void stop();

		std::queue<JNetInPktData> getIncomingPkts();
		void queueOutgoingPkt(const JNetOutPktData& i_cOutPktData);

		void addConnection(const sockaddr_in& i_cDestAddr);

	protected:
	private:
		void queueIncomingPkt();
		void sendNextPkt();
	};
}