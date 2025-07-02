#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <unordered_map>

struct IComponentContainer
{
	virtual ~IComponentContainer() {}
};

template <typename T>
struct ComponentContainer : public IComponentContainer
{
	// Stores the components in densly packed memory
	std::vector<T> dense;

	// Stores the memory offset of a component in dense at the index of an entity id
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
	void addComponent(const uint32_t in_entity, const T& in_component)
	{
		// Get the components type as a string
		std::string componentType = typeid(in_component).name();

		// Check if a container exists for this component type
		if (!m_componentContainers.contains(componentType))
		{
			// If it doesn't, create a new ComponentContainer of the given component with an id of the given component type
			m_componentContainers.insert(std::pair<std::string, IComponentContainer*>(componentType, new ComponentContainer<T>()));
		}

		// Get a pointer to a generic container
		IComponentContainer* genericContainer = m_componentContainers[componentType];

		// Cast it to a pointer to a container of the given type
		ComponentContainer<T>* componentContainer = static_cast<ComponentContainer<T>*>(genericContainer);
		
		// Add the given component to the dense vector
		componentContainer->dense.push_back(in_component);

		// Add the memory offset of the component in dense vector to the index of the entity in sparse
		componentContainer->sparse.insert(componentContainer->sparse.begin() + in_entity, componentContainer->dense.size() - 1);
	}

	template<typename T>
	// Remove a component from an entity
	void removeComponent(const uint32_t in_entity)
	{
		// Get the components type as a string
		std::string componentType = typeid(T).name();

		// Early return if a container for that component doesn't exist
		if (!m_componentContainers.contains(componentType)) return;

		// Get a pointer to a generic container
		IComponentContainer* genericContainer = m_componentContainers[componentType];

		// Cast it to a pointer to a container of the given type
		ComponentContainer<T>* componentContainer = static_cast<ComponentContainer<T>*>(genericContainer);

		// Get entity id in sparse of the component at the back of dense
		uint32_t otherEntity = *(std::find(componentContainer->sparse.begin(), componentContainer->sparse.end(), componentContainer->dense.size() - 1));

		// Set the found entities memory offset value in sparse to the offset value of the component that is being removed
		componentContainer->sparse[otherEntity] = componentContainer->sparse[in_entity];

		// Set the memory offset value of the entity who's component is being removed to 1 above the max entity id
		componentContainer->sparse[in_entity] = UINT32_MAX + 1;
		
		// Swap the component that is being removed with the back of the dense vector
		iter_swap(componentContainer->dense.begin() + componentContainer->sparse[in_entity], componentContainer->dense.end() - 1);

		// Remove the last component from the dense vector
		componentContainer->dense.pop_back();
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