#include "core/ECS/ECS.h"

const uint32_t ECS::createEntity()
{
	uint32_t entity;

	if (!m_freedEntityIds.empty())
	{
		entity = m_freedEntityIds.front();
		m_freedEntityIds.pop();
	}
	else
	{
		entity = m_nextEntityId;
		++m_nextEntityId;
	}
	
	m_entities.push_back(entity);
	return entity;
}

void ECS::destroyEntity(const uint32_t in_entity)
{
	auto entityPtr = std::find(m_entities.begin(), m_entities.end(), in_entity);
	if (entityPtr == m_entities.end()) return;

	for (auto pair : m_componentContainers)
	{
		pair.second->remove(in_entity);
	}

	m_entities.erase(entityPtr);
	
	m_freedEntityIds.push(in_entity);
}
