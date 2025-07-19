#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>
#include <core/game base/GameInstance.h>
#include <network/Client.h>

#include "CTestLevel.h"

class CGameInstance : public GameInstance
{
public:
protected:
private:
	Window* const m_cpWindow;
	Renderer* const m_cpRenderer;
	EventHandler* const m_cpEventHandler;

	Client* const m_cpClient;
	std::thread* const m_cpNetworkThread;

public:
	CGameInstance();
	~CGameInstance();

	const uint32_t getNetworkId() const { return m_cpClient->getNetworkId(); }

protected:
private:
	void serverStartedGame();

	static StateMachine* const initStateMachine(Renderer* const i_cpRenderer,
		EventHandler* const i_cpEventHandler, Client* const i_cpClient);
};