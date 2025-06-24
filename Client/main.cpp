#pragma once

#include <Engine.h>
#include <GameInstance.h>
#include <iostream>
#include <atomic>

using namespace std;

int main()
{
	cout << "Starting OnlineGameClient\n";

	// Create an atomic bool that can be safely accessed by multiple threads simultaneously
	atomic<bool> running = true;

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

	// Run the game
	eng->run();

	// Cleanup pointers
	delete eng;
	eng = nullptr;

	gInst = nullptr;

	cout << "Ended OnlineGameClient\n";

	return 0;
}