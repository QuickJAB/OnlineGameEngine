#include "JNet/JNetPeer.h"

#include <chrono>

#include "JNet/JNetPackets.h"
#include "core/Serializer.h"

JNet::JNetPeer::JNetPeer(const uint8_t i_cuMaxConnections, bool i_bIsHost) :
	m_cuMaxConnections(i_cuMaxConnections), m_bIsHost(i_bIsHost)
{
	JNet::init();
}

JNet::JNetPeer::~JNetPeer()
{
	JNet::cleanup();
}

void JNet::JNetPeer::openSocketForConnections(const uint16_t i_cuPort)
{
	JNet::bindSocket(JNet::createAddr("", i_cuPort));
	m_bRunning = true;
}

bool JNet::JNetPeer::tryConnect(const std::string i_csIP, const uint16_t i_cuPort)
{
	const sockaddr_in cServerAddr = JNet::createAddr(i_csIP, i_cuPort);

	JNet::bindSocket(cServerAddr);
	JNet::overrideSocketTimeout(m_cullConnectionAttemptDelayMilli);
	m_uNumConnectionAttempts = 0;

	JNet::RequestConnectPkt pkt;
	const std::string csPktData = pkt.serialize();

	std::string sData;
	sockaddr_in receiveAddr;
	
	while (m_uNumConnectionAttempts < m_cuMaxConnectionAttempts)
	{
		JNet::send(csPktData, cServerAddr);
		if (JNet::receive(sData, receiveAddr) <= 0)
		{
			++m_uNumConnectionAttempts;
			continue;
		}

		if (receiveAddr.sin_addr.s_addr != cServerAddr.sin_addr.s_addr)
		{
			++m_uNumConnectionAttempts;
			continue;
		}

		if (BinarySerializer::deserialize<JNetPktType>(sData) == JNet::Connected)
		{
			JNet::resetSocketTimeout();
			m_bRunning = true;
			return true;
		}
	}

	return false;
}

void JNet::JNetPeer::update()
{
	unsigned long long ullTick = getCurrentTime();
	unsigned long long ullPrevTick = ullTick;
	unsigned long long ullTickAcum = 0;

	while (m_bRunning)
	{
		queueIncomingPkt();
		sendNextPkt();

		if (!m_bShouldHeartbeat) return;

		ullTick = getCurrentTime();
		ullTickAcum += ullTick - ullPrevTick;
		ullPrevTick = ullTick;
		if (ullTickAcum >= m_cuHeartBeatTimeMilli)
		{
			checkTimeouts();
			dispatchHeartBeat();
			ullTickAcum -= m_cuHeartBeatTimeMilli;
		}

		handleDisconnects();
	}
}

void JNet::JNetPeer::stop()
{
	m_bRunning = false;
}

void JNet::JNetPeer::queueOutgoingPkt(const JNetOutPktData& i_cOutPktData)
{
	m_mutOutPkts.lock();
	m_qOutPkts.push(i_cOutPktData);
	m_mutOutPkts.unlock();
}

void JNet::JNetPeer::processIncomingPkts()
{
	std::queue<JNet::JNetInPktData> qInPkts = getIncomingPkts();
	JNet::JNetPktType pktType;
	while (!qInPkts.empty())
	{
		JNet::JNetInPktData inPktData = qInPkts.front();
		qInPkts.pop();

		pktType = BinarySerializer::deserialize<JNetPktType>(inPktData.sData);
		switch (pktType)
		{
		case JNet::RequestConnect:
			addConnection(inPktData.addr);
			break;
		case JNet::Ping:
			onPinged(inPktData);
			break;
		case JNet::Pong:
			calcOffsetTime(inPktData);
			break;
		case JNet::Disconnect:
			onDisconnected(inPktData.addr);
			break;
		default:
			break;
		}
	}
}

void JNet::JNetPeer::queueIncomingPkt()
{
	JNet::JNetInPktData pktData;
	if (JNet::receive(pktData.sData, pktData.addr))
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
	m_umNetOffsetTime.insert(std::pair<uint8_t, unsigned long long>(m_uNextConnectionID, 0));
	m_umLastPongTime.insert(std::pair<uint8_t, unsigned long long>(m_uNextConnectionID, getCurrentTime()));
	++m_uNextConnectionID;
}

void JNet::JNetPeer::dispatchHeartBeat()
{
	if (m_umConnections.empty()) return;

	PingPkt pkt;
	pkt.ullSentTime = getCurrentTime();
	const std::string sData = pkt.serialize();

	for (auto it = m_umConnections.begin(); it != m_umConnections.end(); ++it)
	{
		JNet::send(sData, it->second);
	}
}

void JNet::JNetPeer::onPinged(JNetInPktData& i_iPktData)
{
	// Make this more streamlined so I don't need to deserialize and reserialize the sent time
	PongPkt pkt;
	pkt.ullSentTime = BinarySerializer::deserialize<unsigned long long>(i_iPktData.sData);
	pkt.ullReceivedTime = getCurrentTime();
	const std::string sData = pkt.serialize();

	JNet::send(sData, i_iPktData.addr);
}

void JNet::JNetPeer::calcOffsetTime(JNetInPktData& i_iPktData)
{
	PongPkt pkt;
	pkt.deserialize(i_iPktData.sData);

	uint8_t uConnectionID = 0;
	for (auto it = m_umConnections.begin(); it != m_umConnections.end(); ++it)
	{
		if (it->second.sin_addr.s_addr == i_iPktData.addr.sin_addr.s_addr)
		{
			uConnectionID = it->first;
			break;
		}
	}

	auto itOffset = m_umNetOffsetTime.find(uConnectionID);
	
	const float cfDeltaTime = static_cast<float>(pkt.ullReceivedTime - pkt.ullSentTime) * 0.5f;
	itOffset->second = pkt.ullReceivedTime - (pkt.ullSentTime + static_cast<unsigned long long>(cfDeltaTime));

	auto itPong = m_umLastPongTime.find(uConnectionID);
	itPong->second = getCurrentTime();
}

unsigned long long JNet::JNetPeer::getCurrentTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void JNet::JNetPeer::checkTimeouts()
{
	const unsigned long long cullCurTime = getCurrentTime();
	for (auto it = m_umLastPongTime.begin(); it != m_umLastPongTime.end(); ++it)
	{
		if (cullCurTime >= it->second + m_cuTimeoutTimeMilli)
		{
			m_sPendingDisconnects.insert(it->first);
		}
	}
}

void JNet::JNetPeer::handleDisconnects()
{
	if (m_sPendingDisconnects.empty()) return;

	DisconnectPkt pkt;
	const std::string csData = pkt.serialize();

	for (const uint8_t cuConnectionID : m_sPendingDisconnects)
	{
		JNet::send(csData, m_umConnections.at(cuConnectionID));
		m_umConnections.erase(cuConnectionID);
		m_umNetOffsetTime.erase(cuConnectionID);
		m_umLastPongTime.erase(cuConnectionID);
	}

	m_sPendingDisconnects.clear();
}

void JNet::JNetPeer::onDisconnected(const sockaddr_in& i_crAddr)
{
	for (auto it = m_umConnections.begin(); it != m_umConnections.end(); ++it)
	{
		m_sPendingDisconnects.insert(it->first);
	}
}
