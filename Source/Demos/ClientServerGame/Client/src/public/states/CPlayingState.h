#pragma once

#include <core/Delegates.h>

#include <states/GPlayingState.h>

namespace JNet
{
	class JNetPeer;
}

class Renderer;
class EventHandler;
class Level;
class CTestLevel;

class CPlayingState : public GPlayingState
{
public:
protected:
private:
	Renderer* const m_cpRenderer;
	EventHandler* const m_cpEventHandler;
	JNet::JNetPeer* const m_cpServer;

public:
	CPlayingState(Renderer* const i_cpRenderer, EventHandler* const i_cpEventHandler,
		JNet::JNetPeer* const i_cpServer);
	~CPlayingState() = default;

	virtual void enter() override;
	virtual std::string update(float i_fDt) override;
	virtual void exit() override;

protected:
private:
	CTestLevel* getLevel();
};