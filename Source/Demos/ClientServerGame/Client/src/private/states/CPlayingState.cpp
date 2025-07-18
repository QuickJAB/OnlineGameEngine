#include "states/CPlayingState.h"

#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include "CTestLevel.h"

using namespace std;

void CPlayingState::enter()
{
	m_pRenderer = m_unidRequestRenderer.broadcast();
	m_pEventHandler = m_unidRequestEventHandler.broadcast();
	m_uPlayerId = m_unidRequestPlayerId.broadcast();

	m_pLevel = new CTestLevel();
	getLevel()->load();
}

string CPlayingState::update(float in_dt)
{
	m_pEventHandler->pollEvents();
	m_pLevel->update(in_dt);
	m_pRenderer->draw(getLevel()->getSprites());

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
