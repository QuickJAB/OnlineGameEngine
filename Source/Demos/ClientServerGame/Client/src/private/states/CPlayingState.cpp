#include "states/CPlayingState.h"

#include <graphics/Renderer.h>
#include <input/EventHandler.h>

#include "CTestLevel.h"

using namespace std;

void CPlayingState::enter()
{
	m_renderer = requestRenderer.broadcast();
	m_eventHandler = requestEventHandler.broadcast();

	m_level = new CTestLevel();
	getLevel()->load();
}

string CPlayingState::update(float in_dt)
{
	m_eventHandler->pollEvents();
	m_level->update(in_dt);
	m_renderer->draw(getLevel()->getSprites());

	return "";
}

void CPlayingState::exit()
{
	delete m_level;
	m_level = nullptr;
}

CTestLevel* CPlayingState::getLevel()
{
	return static_cast<CTestLevel*>(m_level);
}
