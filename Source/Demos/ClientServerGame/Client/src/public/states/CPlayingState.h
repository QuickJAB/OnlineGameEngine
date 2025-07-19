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
	Delegate<const uint32_t()> m_unidRequestNetworkId;

protected:
private:
	Renderer* const m_cpRenderer;
	EventHandler* const m_cpEventHandler;

	uint32_t m_uNetworkId = (uint32_t)-1;

public:
	CPlayingState(Renderer* const i_cpRenderer, EventHandler* const i_cpEventHandler);
	~CPlayingState() = default;

	virtual void enter() override;
	virtual std::string update(float i_fDt) override;
	virtual void exit() override;

protected:
private:
	CTestLevel* getLevel();
};