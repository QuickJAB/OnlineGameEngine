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

	// Stores the memory offset of a component in dense at the index of the owning entity
	std::vector<size_t> sparse;

	template <typename T>
	void add(const uint32_t in_entity)
	{
		dense.push_back(T());

		// Set the index at entity in sparse to the memory offset of the component in dense
		sparse.insert(sparse.begin() + in_entity, dense.size() - 1);
	}

	template <typename T>
	void remove(const uint32_t in_entity)
	{
		if (dense.empty()) return;

		// Get a pointer to the entity in sparse for the component at the back of dense
		auto it = std::find(sparse.begin(), sparse.end(), dense.size() - 1);

		// Swap the component at the back of dense with with one that's being removed
		iter_swap(dense.begin() + sparse[in_entity], dense.end() - 1);

		dense.pop_back();

		// Update the swapped entities memory offset in sparse to the new value
		sparse[it - sparse.begin()] = sparse[in_entity];

		sparse[in_entity] = (size_t)-1;
	}

	template <typename T>
	T* get(const uint32_t in_entity)
	{
		if (dense.empty()) return nullptr;

		size_t memOffset = sparse[in_entity];

		if (memOffset > dense.size() - 1) return nullptr;

		return &dense[memOffset];
	}
};

class ECS
{
public:
	ECS() = default;
	~ECS() = default;

	const uint32_t createEntity();
	void destroyEntity(const uint32_t in_entity);

	template <typename T>
	void addComponent(const uint32_t in_entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), in_entity) == m_entities.end()) return;

		// Try and get a pointer to the container of the given component
		ComponentContainer<T>* componentContainer = tryGetComponentContainer<T>();

		// Check if a container exists for this component type
		if (componentContainer == nullptr)
		{
			componentContainer = createComponentContainer<T>();

			// Set a default size of the sparse array to be 100 (THIS IS W.I.P)
			componentContainer->sparse.resize(100, (size_t)-1);
		}

		componentContainer->add<T>(in_entity);
	}

	template <typename T>
	void removeComponent(const uint32_t in_entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), in_entity) == m_entities.end()) return;

		ComponentContainer<T>* componentContainer = tryGetComponentContainer<T>();
		if (componentContainer == nullptr) return;

		componentContainer->remove<T>(in_entity);
	}

	template <typename T>
	T* getComponent(const uint32_t in_entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), in_entity) == m_entities.end()) return;

		ComponentContainer<T>* componentContainer = tryGetComponentContainer<T>();
		if (componentContainer == nullptr) return nullptr;

		return componentContainer->get<T>(in_entity);
	}

private:
	// The id to be given to the next created entity
	uint32_t m_nextEntityId = 0;

	// Previously used entity ids ready for reassignment
	std::queue<uint32_t> m_freedEntityIds;

	std::vector<uint32_t> m_entities;

	// A map of component type to component container
	std::unordered_map<std::string, IComponentContainer*> m_componentContainers;

	template <typename T>
	ComponentContainer<T>* tryGetComponentContainer()
	{
		// Get the components type as a string
		std::string componentType = typeid(T).name();

		if (!m_componentContainers.contains(componentType)) return nullptr;

		// Cast the pointer to the correct type and return a pointer to it
		return static_cast<ComponentContainer<T>*>(m_componentContainers[componentType]);
	}

	template <typename T>
	ComponentContainer<T>* createComponentContainer()
	{
		// Get the components type as a string
		std::string componentType = typeid(T).name();

		ComponentContainer<T>* container = new ComponentContainer<T>();

		// Add the new container at key component type to the map
		m_componentContainers.insert(std::pair<std::string, IComponentContainer*>(componentType, container));

		return container;
	}
};