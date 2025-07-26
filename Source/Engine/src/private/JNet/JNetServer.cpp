#include "JNet/JNetServer.h"

JNet::JNetServer::JNetServer(const u_short i_cuPort)
{
	JNet::init();

	JNet::bindSocket(JNet::createAddr("", i_cuPort));

	m_bRunning = true;
}

JNet::JNetServer::~JNetServer()
{
	JNet::cleanup();
}

void JNet::JNetServer::update()
{
	while (m_bRunning)
	{
		queueIncomingPkt();
	}
}

void JNet::JNetServer::stop()
{
	m_bRunning = false;
}

std::queue<std::string> JNet::JNetServer::getIncomingPackets()
{
	std::queue<std::string> qPkts;
	m_mutInPkts.lock();
	while (!m_qInPkts.empty())
	{
		qPkts.push(m_qInPkts.front());
		m_qInPkts.pop();
	}
	m_mutInPkts.unlock();
	return qPkts;
}

void JNet::JNetServer::queueIncomingPkt()
{
	std::string sPktData;
	if (JNet::receive(sPktData))
	{
		m_mutInPkts.lock();
		m_qInPkts.push(sPktData);
		m_mutInPkts.unlock();
	}
}
