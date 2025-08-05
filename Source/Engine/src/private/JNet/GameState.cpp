#include "jNet/GameState.h"

#include "core/game base/Controller.h"
#include "jNet/JNetPeer.h"
#include "jNet/JNetPackets.h"

GameState::GameState(JNet::JNetPeer* const i_cpPeer) : m_cpPeer(i_cpPeer)
{
	m_cpPeer->m_unidProcessGamePkt.bind(this, &GameState::processIncomingPkts);
}

GameState::~GameState()
{
	m_cpPeer->m_unidProcessGamePkt.unbind();

	for (auto pIt = m_umControllers.begin(); pIt != m_umControllers.end(); ++pIt)
	{
		delete pIt->second;
	}

	m_umControllers.clear();
}

void GameState::addController(const uint8_t i_cuConnectionId, Controller* const i_cpController)
{
	m_umControllers.insert(std::pair<uint8_t, Controller*>(i_cuConnectionId, i_cpController));
}

Controller* const GameState::getController(const uint8_t i_cuConnectionId)
{
	if (m_umControllers.contains(i_cuConnectionId))
	{
		return m_umControllers.at(i_cuConnectionId);
	}
	return nullptr;
}
