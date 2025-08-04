#include "states/CPlayingState.h"

#include <graphics/Renderer.h>
#include <input/EventHandler.h>
#include <jNet/JNetPeer.h>

#include <GGameState.h>

#include "CTestLevel.h"
#include "CPlayerController.h"

using namespace std;

CPlayingState::CPlayingState(Renderer* const i_cpRenderer, EventHandler* const i_cpEventHandler,
	JNet::JNetPeer* const i_cpServer) :
	GPlayingState(new GGameState(i_cpServer), i_cpServer), m_cpRenderer(i_cpRenderer), m_cpEventHandler(i_cpEventHandler)
{
}

void CPlayingState::enter()
{
	m_pLevel = new CTestLevel(m_cpServer->getConnectionID());
	getLevel()->load();

	const uint32_t playerId = m_pLevel->getPlayerByNetworkId(m_cpServer->getConnectionID());
	CPlayerController* const cpPlayerController = new CPlayerController(playerId, m_pLevel, m_cpEventHandler,
		m_cpServer);
	m_cpGameState->addController(playerId, cpPlayerController);
}

string CPlayingState::update(float in_dt)
{
	m_cpEventHandler->pollEvents();
	getLevel()->update(in_dt);
	m_cpRenderer->draw(getLevel()->getSprites());

	return "";
}

void CPlayingState::exit()
{
	delete m_pLevel;
	m_pLevel = nullptr;
}

CTestLevel* CPlayingState::getLevel()
{
	return static_cast<CTestLevel*>(m_pLevel);
}
