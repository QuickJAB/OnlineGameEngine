#include "core/ECS/ECS.h"

using namespace std;

const uint32_t ECS::createEntity()
{
	uint32_t uEntity;

	if (!m_qFreedEntityIds.empty())
	{
		uEntity = m_qFreedEntityIds.front();
		m_qFreedEntityIds.pop();
	}
	else
	{
		uEntity = m_uNextEntityId;
		++m_uNextEntityId;
	}
	
	m_vEntities.push_back(uEntity);
	return uEntity;
}

void ECS::destroyEntity(const uint32_t i_uEntity)
{
	auto pEntity = std::find(m_vEntities.begin(), m_vEntities.end(), i_uEntity);
	if (pEntity == m_vEntities.end()) return;

	for (auto pair : m_umComponentContainers)
	{
		pair.second->remove(i_uEntity);
	}

	m_vEntities.erase(pEntity);
	
	m_qFreedEntityIds.push(i_uEntity);
}

ECS::~ECS()
{
	if (m_umComponentContainers.empty())
	{
		return;
	}

	for (pair<string, IComponentContainer*> pair : m_umComponentContainers)
	{
		delete pair.second;
	}
}