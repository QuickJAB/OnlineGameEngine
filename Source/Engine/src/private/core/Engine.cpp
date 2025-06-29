#include "core/Engine.h"

#include <print>
#include <chrono>

#include "core/game base/GameInstance.h"

using namespace std;

bool Engine::init(GameInstance* in_gInst)
{
	println("Initializing engine...");

	bool success = true;

	if (in_gInst == nullptr)
	{
		println("ERROR: Attempted to initalize engine with an invalid GameInstace!");
		return false;
	}
	m_gInst = in_gInst;
	success &= m_gInst->init();

	println("Engine initialized!");

	return success;
}

void Engine::run()
{
	println("Started engine");

	// Setup time variables
	float tickAcum = 0.f;
	auto lastTick = chrono::high_resolution_clock::now();

	while (m_running.load())
	{
		// Calculate delta time and add it to the tick accumulator
		auto currentTick = chrono::high_resolution_clock::now();
		chrono::duration<float, milli> diff = currentTick - lastTick;
		float dt = diff.count();
		tickAcum += dt;
		lastTick = currentTick;

		// Call update on non-fixed time updates here
		m_gInst->update(dt);

		// Fixed time-step update
		if (tickAcum >= m_fixedTimeStep)
		{
			// Call update on fixed time updates here
			m_gInst->fixedUpdate(tickAcum);

			// Remove the time step amount from the tick accumulator instead of setting it to 0 to avoid tick drift
			tickAcum -= m_fixedTimeStep;
		}

		// Check if the game instance has requested to quit
		if (m_gInst->shouldQuit())
		{
			m_running.store(false);
		}
	}

	cleanup();
}

void Engine::cleanup()
{
	println("Closing engine...");

	// Cleanup the game
	m_gInst->cleanup();
	delete m_gInst;
	m_gInst = nullptr;

	println("Engine closed");
}