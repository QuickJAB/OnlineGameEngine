#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <unordered_map>

#include <print>

struct IComponentContainer
{
	virtual ~IComponentContainer() {}
};

template <typename T>
struct ComponentContainer : public IComponentContainer
{
	std::vector<T> dense;
	std::vector<size_t> sparse;
};

class ECS
{
public:
	ECS() = default;
	~ECS() = default;

	// Create an entity
	const uint32_t createEntity();

	// Destroy an entity and all its components
	void destroyEntity(const uint32_t in_entity);

	template <typename T>
	// Add a component to an entity
	void addComponent(const uint32_t in_entity, const std::string& in_componentType, const T& in_component)
	{
		// Check if a container exists for this component type
		if (!m_componentContainers.contains(in_componentType))
		{
			// If it doesn't, create a new ComponentContainer of the given component with an id of the given component type
			m_componentContainers.insert(std::pair<std::string, IComponentContainer*>(in_componentType, new ComponentContainer<T>()));
		}

		// Get a pointer to a generic container
		IComponentContainer* genericContainer = m_componentContainers[in_componentType];

		// Cast it to a pointer to a container of the given type
		ComponentContainer<T>* componentContainer = static_cast<ComponentContainer<T>*>(genericContainer);
		
		// Add the given component to the containers vector
		componentContainer->dense.push_back(in_component);

		// Add the position of the component in dense to the index of the entity in sparse
		componentContainer->sparse.insert(componentContainer->sparse.begin() + in_entity, componentContainer->dense.size() - 1);
	}

private:
	// The id to be given to the next entity that is created
	uint32_t m_nextEntityId = 0;

	// A store of ids that can be reused as their entity has been destroyed
	std::queue<uint32_t> m_freedEntityIds;

	// A store of all current entities
	std::vector<uint32_t> m_entities;

	// A map with the component type as the key and a pointer to its container as the value
	std::unordered_map<std::string, IComponentContainer*> m_componentContainers;
};