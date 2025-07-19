#pragma once

#include <atomic>

#include <core/Engine.h>
#include <network/Server.h>

#include "SGameInstance.h"

using namespace std;

int main()
{
	atomic<bool> bRunning;
	bRunning.store(true);

	HostConfig hostConfig;
	hostConfig.pcAddress = Server::createAddress(19);
	hostConfig.ullMaxConnections = 2;

	Server* const cpServer = new Server(bRunning, 0.f, hostConfig);

	SGameInstance* const cpGameInst = new SGameInstance(bRunning, cpServer);

	Engine* const cpE = new Engine(cpGameInst);

	delete cpE;

	return 0;
}