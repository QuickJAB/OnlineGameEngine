#include "CTestLevel.h"

#include <vector>

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

using namespace std;

CTestLevel::CTestLevel(const uint32_t i_uNetworkId) : GTestLevel(),
	m_cuNetworkId(i_uNetworkId), m_cpDrawSys(new DrawSys(m_cpECS))
{
}

CTestLevel::~CTestLevel()
{
	delete m_cpDrawSys;
}

void CTestLevel::update(float i_fDt)
{
	__super::update(i_fDt);

	m_cpDrawSys->update();
}

void CTestLevel::load()
{
	__super::load();

	const vector<uint32_t>* const cpcvEntities = m_cpECS->getEntities();
	for (auto pIt = cpcvEntities->begin(); pIt != cpcvEntities->end(); ++pIt)
	{
		m_cpECS->addComponent<SpriteComp>(*pIt);
	}

	for (auto it = m_umNetPlayerId.begin(); it != m_umNetPlayerId.end(); ++it)
	{
		getComponent<SpriteComp>(it->second)->colour = it->first == m_cuNetworkId ? m_cAllyColour : m_cEnemyColour;
	}
}

vector<SpriteComp>* const CTestLevel::getSprites()
{
	return m_cpECS->getComponentArray<SpriteComp>();
}
