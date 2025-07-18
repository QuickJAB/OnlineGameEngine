#include "CTestLevel.h"

#include <vector>

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

using namespace std;

CTestLevel::CTestLevel(const uint32_t i_uNetworkId) : GTestLevel(),
	m_cuNetworkId(i_uNetworkId)
{
	m_pDrawSys = new DrawSys(m_pECS);
}

CTestLevel::~CTestLevel()
{
	delete m_pDrawSys;
	m_pDrawSys = nullptr;
}

void CTestLevel::update(float i_fDt)
{
	__super::update(i_fDt);

	m_pDrawSys->update();
}

void CTestLevel::load()
{
	__super::load();

	const vector<uint32_t>* cpvEntities = m_pECS->getEntities();
	for (auto pIt = cpvEntities->begin(); pIt != cpvEntities->end(); ++pIt)
	{
		m_pECS->addComponent<SpriteComp>(*pIt);
	}

	for (auto it = m_umNetPlayerId.begin(); it != m_umNetPlayerId.end(); ++it)
	{
		getComponent<SpriteComp>(it->second)->colour = it->first == m_cuNetworkId ? m_allyColour : m_enemyColour;
	}
}

vector<SpriteComp>* CTestLevel::getSprites()
{
	return m_pECS->getComponentArray<SpriteComp>();
}
