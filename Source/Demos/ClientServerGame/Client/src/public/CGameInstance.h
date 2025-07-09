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

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	Client* m_client = nullptr;
	std::thread* m_networkThread = nullptr;

	void initWindow();

	void startNetworkThread();
};