#pragma once

#include <Server.h>

enum EngineMode
{
	client,
	server
};

class Engine
{
public:
	Engine(EngineMode in_mode);
	~Engine() = default;

	bool init();
	void run();

private:
	// General
	bool m_running = false;
	float m_fixedTimeStep = 0.f;

	EngineMode m_mode = EngineMode::client;

	void cleanup();

	// Network
	Server* m_server = nullptr;
	bool initNetwork();
};

