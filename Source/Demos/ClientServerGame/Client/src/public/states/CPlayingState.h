#pragma once

#include <core/state machine/State.h>
#include <core/Delegates.h>

class Renderer;
class EventHandler;
class Level;
class CTestLevel;

class CPlayingState : public State
{
public:
	virtual void enter() override;
	virtual std::string update(float in_dt) override;
	virtual void exit() override;

	Delegate<Renderer*()> requestRenderer;
	Delegate<EventHandler*()> requestEventHandler;

private:
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	CTestLevel* m_level = nullptr;
};