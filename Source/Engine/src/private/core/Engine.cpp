#include "core/Engine.h"

#include <chrono>

using namespace std;

Engine::Engine(GameInstance* const i_pcGameInstance) :
	m_cpGameInstance(i_pcGameInstance)
{
	if (m_cpGameInstance == nullptr) return;
	run();
}

void Engine::run()
{
	using namespace chrono;

	auto lastTick = high_resolution_clock::now();
	auto currentTick = high_resolution_clock::now();
	float fDt = 0.f;

	while (m_cpGameInstance->isRunning())
	{
		currentTick = high_resolution_clock::now();
		duration<float, milli> diff = currentTick - lastTick;
		fDt = diff.count();
		lastTick = currentTick;

		m_cpGameInstance->update(fDt);
	}
}

Engine::~Engine()
{
	delete m_cpGameInstance;
}
