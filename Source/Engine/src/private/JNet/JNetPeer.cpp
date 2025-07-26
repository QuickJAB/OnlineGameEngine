#include "JNet/JNetPeer.h"

#include <print>

JNet::JNetPeer::JNetPeer(const u_short i_cuPort)
{
	JNet::init();

	JNet::bindSocket(JNet::createAddr("", i_cuPort));

	m_bRunning = true;
}

JNet::JNetPeer::~JNetPeer()
{
	JNet::cleanup();
}

void JNet::JNetPeer::update()
{
	while (m_bRunning)
	{
		queueIncomingPkt();
		sendNextPkt();
	}
}

void JNet::JNetPeer::stop()
{
	m_bRunning = false;
}

std::queue<JNet::JNetInPktData> JNet::JNetPeer::getIncomingPkts()
{
	std::queue<JNet::JNetInPktData> qPkts;
	m_mutInPkts.lock();
	while (!m_qInPkts.empty())
	{
		qPkts.push(m_qInPkts.front());
		m_qInPkts.pop();
	}
	m_mutInPkts.unlock();
	return qPkts;
}

void JNet::JNetPeer::queueOutgoingPkt(const JNetOutPktData& i_cOutPktData)
{
	m_mutOutPkts.lock();
	m_qOutPkts.push(i_cOutPktData);
	m_mutOutPkts.unlock();
}

void JNet::JNetPeer::queueIncomingPkt()
{
	JNet::JNetInPktData pktData;
	if (JNet::receive(pktData.sData, pktData.sIP))
	{
		m_mutInPkts.lock();
		m_qInPkts.push(pktData);
		m_mutInPkts.unlock();
	}
}

void JNet::JNetPeer::sendNextPkt()
{
	JNet::JNetOutPktData pktData;
	
	m_mutOutPkts.lock();

	if (m_qOutPkts.empty())
	{
		m_mutOutPkts.unlock();
		return;
	}

	pktData = m_qOutPkts.front();
	m_qOutPkts.pop();
	m_mutOutPkts.unlock();

	if (pktData.iDestID == -1)
	{
		for (auto it = m_umConnections.begin(); it != m_umConnections.end(); ++it)
		{
			JNet::send(pktData.sData, it->second);
		}
	}
	else
	{
		JNet::send(pktData.sData, m_umConnections.at(pktData.iDestID));
	}
}

void JNet::JNetPeer::addConnection(const sockaddr_in& i_cDestAddr)
{
	if (!m_umConnections.empty())
	{
		for (auto it = m_umConnections.begin(); it != m_umConnections.end(); ++it)
		{
			if (it->second.sin_addr.s_addr == i_cDestAddr.sin_addr.s_addr)
			{
				return;
			}
		}
	}
	
	m_umConnections.insert(std::pair<uint8_t, sockaddr_in>(m_uNextConnectionID, i_cDestAddr));
	++m_uNextConnectionID;
}