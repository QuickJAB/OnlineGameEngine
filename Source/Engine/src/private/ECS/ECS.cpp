#include "ECS/ECS.h"

const uint32_t ECS::createEntity()
{
	uint32_t entity;

	// If there are available freed ids in the queue, use that id as preference
	if (!m_freedEntityIds.empty())
	{
		entity = m_freedEntityIds.front();
		m_freedEntityIds.pop();
	}
	else // Otherwise use the next available new id and increment the counter
	{
		entity = m_nextEntityId;
		++m_nextEntityId;
	}
	
	// Add the entity to the set and return a copy of it
	m_entities.push_back(entity);
	return entity;
}

template<typename... Components>
const uint32_t ECS::createEntity(Components... in_components)
{
	// Create the entity using the default method
	const uint32_t entity = createEntity();

	// TODO: Loop through the provided components and add them to the containers
}

void ECS::destroyEntity(const uint32_t& in_entity)
{
	// Early return if the given id isn't a valid entity
	auto entityPtr = std::find(m_entities.begin(), m_entities.end(), in_entity);
	if (entityPtr == m_entities.end()) return;

	// TODO: Remove all components associate with the entity

	// Remove the entity from the vector
	m_entities.erase(entityPtr);
	
	// Add the destroyed entities id to the queue of freed ids for reuse
	m_freedEntityIds.push(in_entity);
}
