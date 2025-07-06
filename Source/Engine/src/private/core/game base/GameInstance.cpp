#include "core/game base/GameInstance.h"

using namespace std;

GameInstance::GameInstance()
{
	m_running.store(true);
}

void GameInstance::update(float in_dt)
{
	if (m_level == nullptr || m_gameMode == nullptr) return;

	m_gameMode->update(in_dt);
	m_level->update(in_dt);
}