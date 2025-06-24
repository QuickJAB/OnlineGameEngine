#pragma once

#include <Engine.h>
#include <GameInstance.h>
#include <iostream>
#include <atomic>
#include <Server.h>

using namespace std;

int main()
{
	cout << "Starting OnlineGameServer\n";

	// Create an atomic bool that can be safely accessed by multiple threads simultaneously
	atomic<bool> running = true;

	// Create and init the server engine module
	Server* server = new Server(running);
	if (server == nullptr)
	{
		cout << "ERROR: Failed to create the server!\n";
		return 1;
	}

	if (!server->init())
	{
		cout << "ERROR: Failed to init the server!\n";
		return 1;
	}

	// This will be initalized and cleanedup by the engine
	GameInstance* gInst = new GameInstance();

	// Create and inialize the engine
	Engine* eng = new Engine(running, 1000.f / 60.f);
	if (eng == nullptr)
	{
		cout << "ERROR: Failed to create the engine!\n";
		return 1;
	}

	if (!eng->init(gInst))
	{
		cout << "ERROR: Failed to initalize the engine!\n";
		return 1;
	}

	// Create and start the server thread
	thread serverThread(&Server::update, server);

	// Run the game
	eng->run();

	// Rejoin the server thread
	serverThread.join();

	// Cleanup engine and reset game instance pointer
	delete eng;
	eng = nullptr;
	gInst = nullptr;

	// Cleanup the server
	server->cleanup();
	delete server;
	server = nullptr;

	cout << "Ended OnlineGameServer\n";

	return 0;
}