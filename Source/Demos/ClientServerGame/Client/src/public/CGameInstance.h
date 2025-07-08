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

	void setIPAndPort(std::string in_ip, uint16_t in_port);
	std::string getIP() const { return m_ip; }
	uint16_t getPort() const { return m_port; }
	Client* getClient() const { return m_client; }

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;
	Client* m_client = nullptr;

	std::string m_ip;
	uint16_t m_port = 0;

	void initWindow();
};