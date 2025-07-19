#include "core/Engine.h"

#include <chrono>

using namespace std;

Engine::Engine(GameInstance* const i_pcGameInstance) :
	m_pcGameInstance(i_pcGameInstance)
{
	if (m_pcGameInstance == nullptr) return;
	run();
}

void Engine::run()
{
	using namespace chrono;

	auto lastTick = high_resolution_clock::now();
	auto currentTick = high_resolution_clock::now();
	float fDt = 0.f;

	while (m_pcGameInstance->isRunning())
	{
		currentTick = high_resolution_clock::now();
		duration<float, milli> diff = currentTick - lastTick;
		fDt = diff.count();
		lastTick = currentTick;

		m_pcGameInstance->update(fDt);
	}
}

Engine::~Engine()
{
	delete m_pcGameInstance;
}
