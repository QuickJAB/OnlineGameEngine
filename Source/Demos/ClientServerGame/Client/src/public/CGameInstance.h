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
	Window* m_pWindow = nullptr;
	Renderer* m_pRenderer = nullptr;
	EventHandler* m_pEventHandler = nullptr;

	Client* m_pClient = nullptr;
	std::thread* m_pNetworkThread = nullptr;

	long long m_llGameStateTime = 0;

public:
	CGameInstance();
	~CGameInstance();

	Client* getClient() const { return m_pClient; }
	Renderer* getRenderer() const { return m_pRenderer; }
	EventHandler* getEventHandler() const { return m_pEventHandler; }

protected:
private:
	void initWindow();

	void startNetworkThread();

	void serverStartedGame(long long i_llStartTime);
};