#pragma once

#include <atomic>

#include <core/Engine.h>
#include <jNet/JNetPeer.h>

#include "SGameInstance.h"

using namespace std;

int main()
{
	atomic<bool> bRunning;
	bRunning.store(true);

	JNet::JNetPeer* const cpServer = new JNet::JNetPeer(2, true);

	SGameInstance* const cpGameInst = new SGameInstance(bRunning, cpServer);

	Engine* const cpE = new Engine(cpGameInst);

	delete cpE;

	return 0;
}