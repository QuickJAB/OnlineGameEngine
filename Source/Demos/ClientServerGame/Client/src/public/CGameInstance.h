#pragma once

#include <atomic>
#include <thread>

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>
#include <core/game base/GameInstance.h>

#include "CTestLevel.h"

namespace JNet
{
	class JNetPeer;
}

class CGameInstance : public GameInstance
{
public:
protected:
private:
	Window* const m_cpWindow;
	Renderer* const m_cpRenderer;
	EventHandler* const m_cpEventHandler;

	JNet::JNetPeer* const m_cpClient;
	std::thread* const m_cpNetworkThread;

	uint8_t m_uNetworkID;

public:
	CGameInstance(std::atomic<bool>& i_rbRunning, JNet::JNetPeer* const i_cpClient, Window* const i_cpWnd,
		Renderer* const i_cpRenderer, EventHandler* const i_cpEventHandler);
	~CGameInstance();

	const uint8_t getNetworkID() const { return m_uNetworkID; }

protected:
private:
	void serverStartedGame(const uint8_t i_cuPlayerID);

	static StateMachine* const initStateMachine(Renderer* const i_cpRenderer,
		EventHandler* const i_cpEventHandler, JNet::JNetPeer* const i_cpClient);
};