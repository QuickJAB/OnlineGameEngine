#pragma once

#include <atomic>

#include <core/Engine.h>
#include <jNet/JNetPeer.h>

#include "CGameInstance.h"

using namespace std;

int main()
{
	atomic<bool> bRunning;
	bRunning.store(true);

	Window* const cpWnd = new Window("OnlineGame Client", 1920, 1080);

	Renderer* const cpRenderer = new Renderer(cpWnd->getSDLWindow());

	EventHandler* const cpEventHandler = new EventHandler();

	JNet::JNetPeer* const cpClient = new JNet::JNetPeer();

	CGameInstance* const cpGameInst = new CGameInstance(bRunning, cpClient,
		cpWnd, cpRenderer, cpEventHandler);

	Engine* pE = new Engine(cpGameInst);

	delete pE;

	return 0;
}