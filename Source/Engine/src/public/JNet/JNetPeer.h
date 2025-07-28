#pragma once

#include <queue>
#include <mutex>
#include <unordered_map>
#include <set>

#include "JNet.h"
#include "core/Delegates.h"

namespace JNet
{
	enum JNetPktType;

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
		Delegate<void(JNet::JNetPktType, JNet::JNetInPktData&)> m_unidProcessGamePkt;

	protected:
	private:
		bool m_bRunning;
		const bool m_bIsHost;

		std::mutex m_mutInPkts;
		std::queue<JNetInPktData> m_qInPkts;

		std::mutex m_mutOutPkts;
		std::queue<JNetOutPktData> m_qOutPkts;

		uint8_t m_uNextConnectionID = 0;
		const uint8_t m_cuMaxConnections;
		std::unordered_map<uint8_t, sockaddr_in> m_umConnections;

		const uint32_t m_cuHeartBeatTimeMilli = 5000;
		const uint32_t m_cuTimeoutTimeMilli = 30000;
		std::unordered_map<uint8_t, unsigned long long> m_umNetOffsetTime;
		std::unordered_map<uint8_t, unsigned long long> m_umLastPongTime;

		std::set<uint8_t> m_sPendingDisconnects;

		const uint8_t m_cuMaxConnectionAttempts = 10;
		uint8_t m_uNumConnectionAttempts = 0;
		const unsigned long long m_cullConnectionAttemptDelayMilli = 5000;

	public:
		JNetPeer(const uint8_t i_cuMaxConnections = 1, bool i_bIsHost = false);
		~JNetPeer();

		void openSocketForConnections(const uint16_t i_cuPort);
		bool tryConnect(const std::string i_csIP, const uint16_t i_cuPort);

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
		void checkTimeouts();
		void handleDisconnects();
		void onDisconnected(const sockaddr_in& i_crAddr);
	};
}