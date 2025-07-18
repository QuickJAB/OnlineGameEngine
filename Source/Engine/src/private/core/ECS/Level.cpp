#include "core/ECS/Level.h"

#include "core/ECS/ECS.h"

Level::Level()
{
	m_pECS = new ECS();
}

Level::~Level()
{
	delete m_pECS;
	m_pECS = nullptr;
}

void Level::update(float i_fDt)
{
}

void Level::load()
{
}

uint32_t Level::getPlayerByNetworkId(const uint32_t i_uNetworkId)
{
	return m_umNetPlayerId.at(i_uNetworkId);
}