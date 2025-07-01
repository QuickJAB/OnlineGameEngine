#pragma once

#include <cstdint>
#include <queue>
#include <unordered_set>

class ECS
{
public:
	ECS() = default;
	~ECS() = default;

	// Create an entity with no components
	const uint32_t createEntity();

	// Create an entity with specified components
	template<typename... Components>
	const uint32_t createEntity(Components... in_components);

	// Destroy an entity and all its components
	void destroyEntity(const uint32_t& in_entity);

private:
	// The id to be given to the next entity that is created
	uint32_t m_nextEntityId = 0;

	// A store of ids that can be reused as their entity has been destroyed
	std::queue<const uint32_t> m_freedEntityIds;

	// A store of all current entities
	std::unordered_set<const uint32_t> m_entities;
};