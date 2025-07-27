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
		sockaddr_in addr;
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
		const uint8_t m_cuMaxConnections;

		float m_fLastHeartBeatTimeMilli = 0;
		const float m_cfHeartBeatRateMilli = 5000;
		std::unordered_map<uint8_t, unsigned long long> m_umNetOffsetTime;

	public:
		JNetPeer(const std::string i_csIP, const uint16_t i_cuPort, const uint8_t i_cuMaxConnections);
		~JNetPeer();

		void update();
		void stop();

		void queueOutgoingPkt(const JNetOutPktData& i_cOutPktData);
		void processIncomingPkts();

	protected:
	private:
		void queueIncomingPkt();
		void sendNextPkt();
		std::queue<JNetInPktData> getIncomingPkts();
		void addConnection(const sockaddr_in& i_cDestAddr);
		void dispatchHeartBeat();
		void onPinged(JNetInPktData& i_iPktData);
		void calcOffsetTime(JNetInPktData& i_iPktData);
		unsigned long long getCurrentTime();
	};
}