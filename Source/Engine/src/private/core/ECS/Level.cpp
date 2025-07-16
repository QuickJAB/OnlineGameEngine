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
