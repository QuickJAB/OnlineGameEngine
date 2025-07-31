#include "core/ECS/Level.h"

#include "core/ECS/ECS.h"

Level::Level() : m_cpECS(new ECS())
{
}

Level::~Level()
{
	delete m_cpECS;
}

const uint32_t Level::getPlayerByNetworkId(const uint8_t i_cuNetworkId)
{
	return m_umNetPlayerId.at(i_cuNetworkId);
}