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
	CGameInstance();
	~CGameInstance();

	Client* getClient() const { return m_client; }
	Renderer* getRenderer() const { return m_renderer; }
	EventHandler* getEventHandler() const { return m_eventHandler; }

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	Client* m_client = nullptr;
	std::thread* m_networkThread = nullptr;

	int m_playerNum = -1;

	long long m_gameStateTime = 0;

	void initWindow();

	void startNetworkThread();

	void setPlayerNum(int in_playerNum) { m_playerNum = in_playerNum; }

	void serverStartedGame(long long in_startTime);
};