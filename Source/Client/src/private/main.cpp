#pragma once

#include <print>
#include <atomic>
#include <iostream>

#include <core/Engine.h>
#include <graphics/Window.h>
#include <graphics/Renderer.h>
#include <network/Client.h>

#include "CGameInstance.h"

using namespace std;

void connectToServer(Client* in_client)
{
	// TEMPORARY CODE START
	while (true)
	{
		std::string ip;
		print("ip: ");
		cin >> ip;
		if (in_client->tryConnect(ip)) break;
	}
	// TEMPORARY CODE END
}

int main()
{
	println("Starting OnlineGameClient");

	// Create an atomic bool that can be safely accessed by multiple threads simultaneously
	atomic<bool> running = true;

	// Create and init the client engine module
	Client* client = new Client(running);
	if (client == nullptr)
	{
		println("ERROR: Failed to create the client!");
		return 1;
	}

	if (!client->init(NetSettings::ClientSettings::TICK_TIME))
	{
		println("ERROR: Failed to init the client!");
		return 1;
	}

	// TEMPORARY CODE START
	connectToServer(client);
	// TEMPORARY CODE END

	// This will be initalized and cleanedup by the engine
	CGameInstance* gInst = new CGameInstance();

	// Create and inialize the engine
	Engine* eng = new Engine(running, 1000.f / 60.f);
	if (eng == nullptr)
	{
		println("ERROR: Failed to create the engine!");
		return 1;
	}

	if (!eng->init(gInst))
	{
		println("ERROR: Failed to initalize the engine!");
		return 1;
	}

	// Create and start the client thread
	thread clientThread(&Client::update, client);

	// Run the game
	eng->run();

	// Rejoin the client thread
	clientThread.join();

	// Cleanup pointers
	delete eng;
	eng = nullptr;
	gInst = nullptr;

	// Cleanup the server
	client->cleanup();
	delete client;
	client = nullptr;

	println("Ended OnlineGameClient");

	return 0;
}