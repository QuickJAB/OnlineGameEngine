#pragma once

#include <Engine.h>
#include <print>
#include <atomic>
#include <Window.h>
#include <Renderer.h>
#include "CliGameInstance.h"

using namespace std;

int main()
{
	println("Starting OnlineGameClient");

	// Create an atomic bool that can be safely accessed by multiple threads simultaneously
	atomic<bool> running = true;

	// This will be initalized and cleanedup by the engine
	CliGameInstance* gInst = new CliGameInstance();

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

	// Run the game
	eng->run();

	// Cleanup pointers
	delete eng;
	eng = nullptr;
	gInst = nullptr;

	println("Ended OnlineGameClient");

	return 0;
}