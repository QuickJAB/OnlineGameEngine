#include "core/game base/GameInstance.h"

using namespace std;

void GameInstance::update(float in_dt)
{
	if (m_world == nullptr || m_gameMode == nullptr) return;

	m_gameMode->update(in_dt);
	m_world->update(in_dt);
}