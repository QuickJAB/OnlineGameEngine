#pragma once

#include <core/Delegates.h>

#include <states/GPlayingState.h>

class Renderer;
class EventHandler;
class Level;
class CTestLevel;

class CPlayingState : public GPlayingState
{
public:
	virtual void enter() override;
	virtual std::string update(float in_dt) override;
	virtual void exit() override;

	Delegate<Renderer*()> requestRenderer;
	Delegate<EventHandler*()> requestEventHandler;

private:
	CTestLevel* getLevel();

	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;
};