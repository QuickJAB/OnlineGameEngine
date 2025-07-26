#pragma once

#include <queue>
#include <mutex>

#include "JNet.h"

namespace JNet
{
	class JNetServer
	{
	public:
	protected:
	private:
		bool m_bRunning;

		std::queue<std::string> m_qInPkts;
		std::mutex m_mutInPkts;

	public:
		JNetServer(const u_short i_cuPort);
		~JNetServer();

		void update();
		void stop();

		std::queue<std::string> getIncomingPackets();

	protected:
	private:
		void queueIncomingPkt();
	};
}