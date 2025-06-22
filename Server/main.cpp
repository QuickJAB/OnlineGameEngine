#pragma once

#include <Engine.h>
#include <iostream>

using namespace std;

int main()
{
	cout << "Starting OnlineGameServer\n";

	Engine* eng = new Engine(EngineMode::server);
	if (eng == nullptr)
	{
		cout << "ERROR: Failed to create the engine!\n";
		return 1;
	}

	if (!eng->init())
	{
		cout << "ERROR: Failed to initalize the engine!\n";
		return 1;
	}

	eng->run();

	delete eng;
	eng = nullptr;

	cout << "Ended OnlineGameServer\n";

	return 0;
}