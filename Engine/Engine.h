#pragma once

#include <Server.h>

enum EngineMode
{
	singleplayer,
	client,
	server
};

class Engine
{
public:
	Engine(EngineMode in_mode = singleplayer);
	~Engine() = default;

	bool init();
	void run();

private:
	// General
	bool m_running = false;
	float m_fixedTimeStep = 0.f;

	EngineMode m_mode = EngineMode::singleplayer;

	void cleanup();

	// Server
	Server* m_server = nullptr;

	bool initServer();
};

