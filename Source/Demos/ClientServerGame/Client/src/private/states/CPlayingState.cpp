#include "states/CPlayingState.h"

#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include <GGameState.h>

#include "CTestLevel.h"

using namespace std;

CPlayingState::CPlayingState(Renderer* const i_cpRenderer, EventHandler* const i_cpEventHandler) :
	GPlayingState(new GGameState()), m_cpRenderer(i_cpRenderer), m_cpEventHandler(i_cpEventHandler)
{
}

void CPlayingState::enter()
{
	m_uNetworkId = m_unidRequestNetworkId.broadcast();

	m_pLevel = new CTestLevel(m_uNetworkId);
	getLevel()->load();
}

string CPlayingState::update(float in_dt)
{
	m_cpEventHandler->pollEvents();
	m_pLevel->update(in_dt);
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
