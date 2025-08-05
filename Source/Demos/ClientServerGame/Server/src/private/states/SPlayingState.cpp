#include "states/SPlayingState.h"

#include <JNet/JNetPeer.h>

#include <GGameState.h>
#include <GTestLevel.h>
#include <GGamePkts.h>

using namespace std;

SPlayingState::SPlayingState(JNet::JNetPeer* const i_cpServer) : GPlayingState(new GGameState(i_cpServer), i_cpServer)
{
}

void SPlayingState::enter()
{
	m_pLevel = new GTestLevel();
	m_pLevel->load();

	m_cpServer->m_unidProcessGamePkt.bind(this, &SPlayingState::processIncomingPkts);
}

string SPlayingState::update(const float i_cfDt)
{
	m_fTickAcum += i_cfDt;
	if (m_fTickAcum >= m_cfTickRateMilli)
	{
		m_fTickAcum -= m_cfTickRateMilli;

		m_cpServer->processIncomingPkts();
		m_pLevel->update(i_cfDt);
	}

	return "";
}

void SPlayingState::exit()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

void SPlayingState::processIncomingPkts(JNet::JNetPktType i_pktType, JNet::JNetInPktData& i_rPktData)
{
	switch (i_pktType)
	{
	case ClientInput:
		processClientInput(i_rPktData);
		break;
	}
}

void SPlayingState::processClientInput(JNet::JNetInPktData& i_rPktData)
{
	ClientInputPkt pkt;
	pkt.deserialize(i_rPktData.sData);

	Controller* const pController = m_cpGameState->getController(pkt.uPlayerID);

}
