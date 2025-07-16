#include "core/Engine.h"

#include <chrono>

using namespace std;

Engine::Engine(GameInstance* i_pGameInstance) :
	m_pGameInstance(i_pGameInstance)
{
	if (m_pGameInstance == nullptr) return;
	run();
}

void Engine::run()
{
	using namespace chrono;

	auto lastTick = high_resolution_clock::now();
	auto currentTick = high_resolution_clock::now();
	float fDt = 0.f;

	while (m_pGameInstance->isRunning())
	{
		currentTick = high_resolution_clock::now();
		duration<float, milli> diff = currentTick - lastTick;
		fDt = diff.count();
		lastTick = currentTick;

		m_pGameInstance->update(fDt);
	}
}

Engine::~Engine()
{
	delete m_pGameInstance;
	m_pGameInstance = nullptr;
}
