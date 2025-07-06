#include "core/Engine.h"

#include <chrono>

using namespace std;

Engine::Engine(GameInstance* in_gameInstance) :
	m_gameInstance(in_gameInstance)
{
	if (in_gameInstance == nullptr) return;
	run();
}

void Engine::run()
{
	// Declare timing variables
	auto lastTick = chrono::high_resolution_clock::now();
	auto currentTick = chrono::high_resolution_clock::now();
	float dt = 0.f;

	while (m_gameInstance->isRunning())
	{
		// Calculate delta time
		currentTick = chrono::high_resolution_clock::now();
		chrono::duration<float, milli> diff = currentTick - lastTick;
		dt = diff.count();
		lastTick = currentTick;

		m_gameInstance->update(dt);
	}
}

Engine::~Engine()
{
	delete m_gameInstance;
	m_gameInstance = nullptr;
}
