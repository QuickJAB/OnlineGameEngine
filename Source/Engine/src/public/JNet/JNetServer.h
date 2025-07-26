#pragma once

#include <queue>
#include <mutex>

#include "JNet.h"

namespace JNet
{
	struct JNetInPktData
	{
		std::string sData;
		std::string sIP;
	};

	class JNetServer
	{
	public:
	protected:
	private:
		bool m_bRunning;

		std::queue<JNetInPktData> m_qInPkts;
		std::mutex m_mutInPkts;

	public:
		JNetServer(const u_short i_cuPort);
		~JNetServer();

		void update();
		void stop();

		std::queue<JNetInPktData> getIncomingPackets();

	protected:
	private:
		void queueIncomingPkt();
	};
}