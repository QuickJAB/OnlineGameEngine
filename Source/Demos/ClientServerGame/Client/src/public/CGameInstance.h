#pragma once

#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <input/EventHandler.h>
#include <core/game base/GameInstance.h>

#include "CTestLevel.h"

class CGameInstance : public GameInstance
{
public:
	CGameInstance();
	~CGameInstance();

	void setIPAndPort(std::string in_ip, uint16_t in_port);
	std::string getIP() { return m_ip; }
	uint16_t getPort() { return m_port; }

private:
	Window* m_window = nullptr;
	Renderer* m_renderer = nullptr;
	EventHandler* m_eventHandler = nullptr;

	std::string m_ip;
	uint16_t m_port;

	void initWindow();
};