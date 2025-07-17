#include "CTestLevel.h"

#include <vector>

#include <core/ECS/component/TransformComp.h>
#include <core/ECS/component/SpriteComp.h>
#include <core/ECS/component/VelocityComp.h>

using namespace std;

CTestLevel::CTestLevel() : GTestLevel()
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
}

uint32_t CTestLevel::spawnPlayer(float i_fX, float i_fY, bool i_bIsAlly)
{
	uint32_t uPlayerId = __super::spawnPlayer(i_fX, i_fY, i_bIsAlly);

	SpriteComp spriteComp;
	spriteComp.colour = i_bIsAlly ? SDL_Color(0, 255, 0, 255) : SDL_Color(255, 0, 0, 255);
	m_pECS->addComponent<SpriteComp>(uPlayerId, &spriteComp);

	return uPlayerId;
}

std::vector<SpriteComp>* CTestLevel::getSprites()
{
	return m_pECS->getComponentArray<SpriteComp>();
}
