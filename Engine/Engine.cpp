#include "Engine.h"

#include <iostream>

using namespace std;

Engine::Engine(EngineMode in_mode)
{
	m_mode = in_mode;
}

bool Engine::init()
{
	std::cout << "Initializing engine...\n";

	bool success = true;

	success &= initNetwork();

	std::cout << "Engine initialized!\n";
	return success;
}

void Engine::run()
{
	cout << "Started engine\n";

	m_running = true;

	// Create the server thread
	// NOTE - If m_server is nullptr, Server::update will return early so this is "fine"
	thread serverThread(&Server::update, m_server, ref(m_running));

	// Setup time variables
	float tickAcum = 0.f;
	auto lastTick = std::chrono::high_resolution_clock::now();

	while (m_running)
	{
		// Calculate delta time and add it to the tick accumulator
		auto currentTick = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> diff = currentTick - lastTick;
		float dt = diff.count();
		tickAcum += dt;
		lastTick = currentTick;

		// Call update on non-fixed time updates here
		string in;
		cin >> in;
		m_running = in != "exit";

		// Fixed time-step update
		if (tickAcum >= m_fixedTimeStep)
		{
			// Remove the time step amount from the tick accumulator instead of setting it to 0 to avoid tick drift
			tickAcum -= m_fixedTimeStep;

			// Call update on fixed time updates here

		}
	}

	// Rejoin the server thread
	serverThread.join();

	cleanup();
}

void Engine::cleanup()
{
	std::cout << "Closing engine...\n";

	// Cleanup the server
	if (m_server != nullptr)
	{
		m_server->cleanup();
		delete m_server;
		m_server = nullptr;
	}
	
	enet_deinitialize();
}

bool Engine::initNetwork()
{
	std::cout << "Initializing network...\n";

	// Initialize ENet
	if (enet_initialize() != 0)
	{
		cout << "ERROR: Failed to init ENet!\n";
		return false;
	}

	if (m_mode == EngineMode::client) // Create and initalize a client
	{

	}
	else if (m_mode == EngineMode::server) // Create and initalize a server
	{
		m_server = new Server();
		if (m_server == nullptr)
		{
			cout << "ERROR: Failed to create server!\n";
			return false;
		}
		if (!m_server->init())
		{
			cout << "ERROR: Failed to initialize server!\n";
			return false;
		}
	}

	std::cout << "Network initialized!\n";
	return true;
}
