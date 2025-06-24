#include "Engine.h"

#include <iostream>
#include <chrono>

#include "GameInstance.h"

using namespace std;

bool Engine::init(GameInstance* in_gInst)
{
	cout << "Initializing engine...\n";

	bool success = true;

	if (in_gInst == nullptr)
	{
		cout << "ERROR: Attempted to initalize engine with an invalid GameInstace!\n";
		return false;
	}
	m_gInst = in_gInst;
	success &= m_gInst->init();

	cout << "Engine initialized!\n";

	return success;
}

void Engine::run()
{
	cout << "Started engine\n";

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
	}

	cleanup();
}

void Engine::cleanup()
{
	cout << "Closing engine...\n";

	// Cleanup the game
	m_gInst->cleanup();
	delete m_gInst;
	m_gInst = nullptr;
}