#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <unordered_map>
#include <typeinfo>

#include "component/ComponentBase.h"

struct IComponentContainer
{
	virtual ~IComponentContainer() {}

	virtual void remove(const uint32_t in_entity) {}
};

template <typename T>
struct ComponentContainer : public IComponentContainer
{
	std::vector<T> components;

	// Maps entity id to the memory offset of the component in components
	std::unordered_map<uint32_t, size_t> map;

	template <typename T>
	void add(const uint32_t in_entity)
	{
		if (map.contains(in_entity)) return;

		T component = T();
		component.owner = in_entity;

		components.push_back(component);
		map.insert(std::pair<uint32_t, size_t>(in_entity, components.size() - 1));
	}

	void remove(const uint32_t in_entity) override
	{
		if (components.empty() || !map.contains(in_entity)) return;

		// Set the memory offset of the entity that owns the component at the back of components to the offset of the component thats being removed
		map[components.back().owner] = map[in_entity];

		// Swap the component at the back of components with the component thats being removed
		iter_swap(components.begin() + map[in_entity], components.end() - 1);

		components.pop_back();
		map.erase(in_entity);
	}

	template <typename T>
	T* get(const uint32_t in_entity)
	{
		if (components.empty() || !map.contains(in_entity)) return nullptr;

		return &components[map[in_entity]];
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

		ComponentContainer<T>* componentContainer = getComponentContainer<T>();

		if (componentContainer == nullptr)
		{
			componentContainer = createComponentContainer<T>();
		}

		componentContainer->add<T>(in_entity);
	}

	template <typename T>
	void removeComponent(const uint32_t in_entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), in_entity) == m_entities.end()) return;

		ComponentContainer<T>* componentContainer = getComponentContainer<T>();
		if (componentContainer == nullptr) return;

		componentContainer->remove(in_entity);
	}

	template <typename T>
	T* getComponent(const uint32_t in_entity)
	{
		if (std::find(m_entities.begin(), m_entities.end(), in_entity) == m_entities.end()) return nullptr;

		ComponentContainer<T>* componentContainer = getComponentContainer<T>();
		if (componentContainer == nullptr) return nullptr;

		return componentContainer->get<T>(in_entity);
	}

	template <typename T>
	std::vector<T>* getComponentArray()
	{
		ComponentContainer<T>* componentContainer = getComponentContainer<T>();
		if (componentContainer == nullptr) return nullptr;

		return &componentContainer->components;
	}

private:
	uint32_t m_nextEntityId = 0;

	std::queue<uint32_t> m_freedEntityIds;

	std::vector<uint32_t> m_entities;

	// A map of component type to component container
	std::unordered_map<std::string, IComponentContainer*> m_componentContainers;

	template <typename T>
	ComponentContainer<T>* getComponentContainer()
	{
		// Get the components type as a string
		std::string componentType = typeid(T).name();

		if (!m_componentContainers.contains(componentType)) return nullptr;

		// Cast the pointer to the correct type and return
		return static_cast<ComponentContainer<T>*>(m_componentContainers[componentType]);
	}

	template <typename T>
	ComponentContainer<T>* createComponentContainer()
	{
		// Get the components type as a string
		std::string componentType = typeid(T).name();

		ComponentContainer<T>* container = new ComponentContainer<T>();

		m_componentContainers.insert(std::pair<std::string, IComponentContainer*>(componentType, container));

		return container;
	}
};