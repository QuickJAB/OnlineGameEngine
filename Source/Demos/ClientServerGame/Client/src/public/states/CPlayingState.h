#pragma once

#include <core/Delegates.h>

#include <states/GPlayingState.h>

#include "CPlayerController.h"

class Renderer;
class EventHandler;
class Level;
class CTestLevel;

class CPlayingState : public GPlayingState
{
public:
	Delegate<Renderer*()> m_unidRequestRenderer;
	Delegate<EventHandler*()> m_unidRequestEventHandler;
	Delegate<uint32_t()> m_unidRequestPlayerId;

protected:
private:
	Renderer* m_pRenderer = nullptr;
	EventHandler* m_pEventHandler = nullptr;

	uint32_t m_uPlayerId = 0;

public:
	virtual void enter() override;
	virtual std::string update(float i_fDt) override;
	virtual void exit() override;

protected:
private:
	CTestLevel* getLevel();
};