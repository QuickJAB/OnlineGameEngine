#pragma once

#include <cstdint>
#include <queue>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <algorithm>

#include "component/ComponentBase.h"

struct IComponentContainer
{
	virtual ~IComponentContainer() {}

	virtual void remove(const uint32_t i_cuEntity) {}
};

template <typename T>
struct ComponentContainer : public IComponentContainer
{
	std::vector<T> vComponents;

	std::unordered_map<uint32_t, size_t> umMap;

	template <typename T>
	void add(const uint32_t i_cuEntity, const T* i_cpComponent = nullptr)
	{
		if (umMap.contains(i_cuEntity)) return;

		T component = i_cpComponent == nullptr ? T() : *i_cpComponent;
		component.uOwner = i_cuEntity;

		vComponents.push_back(component);
		umMap.insert(std::pair<uint32_t, size_t>(i_cuEntity, vComponents.size() - 1));
	}

	void remove(const uint32_t i_cuEntity) override
	{
		if (vComponents.empty() || !umMap.contains(i_cuEntity)) return;

		umMap[vComponents.back().uOwner] = umMap[i_cuEntity];

		std::iter_swap(vComponents.begin() + umMap[i_cuEntity], vComponents.end() - 1);

		vComponents.pop_back();
		umMap.erase(i_cuEntity);
	}

	template <typename T>
	T* get(const uint32_t i_cuEntity)
	{
		if (vComponents.empty() || !umMap.contains(i_cuEntity)) return nullptr;

		return &vComponents[umMap[i_cuEntity]];
	}

	virtual ~ComponentContainer() override
	{
		umMap.clear();
		vComponents.clear();
	}
};

class ECS
{
public:
protected:
private:
	uint32_t m_uNextEntityId = 0;

	std::queue<uint32_t> m_qFreedEntityIds;

	std::vector<uint32_t> m_vEntities;

	std::unordered_map<std::string, IComponentContainer*> m_umComponentContainers;

public:
	ECS() = default;
	~ECS();

	const uint32_t createEntity();
	void destroyEntity(const uint32_t i_cuEntity);

	template <typename T>
	void addComponent(const uint32_t i_cuEntity, const T* i_cpComponent = nullptr)
	{
		if (std::find(m_vEntities.begin(), m_vEntities.end(), i_cuEntity) == m_vEntities.end()) return;

		ComponentContainer<T>* pComponentContainer = getComponentContainer<T>();

		if (pComponentContainer == nullptr)
		{
			pComponentContainer = createComponentContainer<T>();
		}

		pComponentContainer->add<T>(i_cuEntity, i_cpComponent);
	}

	template <typename T>
	void removeComponent(const uint32_t i_cuEntity)
	{
		if (std::find(m_vEntities.begin(), m_vEntities.end(), i_cuEntity) == m_vEntities.end()) return;

		ComponentContainer<T>* pComponentContainer = getComponentContainer<T>();
		if (pComponentContainer == nullptr) return;

		pComponentContainer->remove(i_cuEntity);
	}

	template <typename T>
	T* getComponent(const uint32_t i_cuEntity)
	{
		if (std::find(m_vEntities.begin(), m_vEntities.end(), i_cuEntity) == m_vEntities.end()) return nullptr;

		ComponentContainer<T>* pComponentContainer = getComponentContainer<T>();
		if (pComponentContainer == nullptr) return nullptr;

		return pComponentContainer->get<T>(i_cuEntity);
	}

	template <typename T>
	std::vector<T>* getComponentArray()
	{
		ComponentContainer<T>* pComponentContainer = getComponentContainer<T>();
		if (pComponentContainer == nullptr) return nullptr;

		return &pComponentContainer->vComponents;
	}

	template <typename T>
	ComponentContainer<T>* getComponentContainer()
	{
		std::string sComponentType = typeid(T).name();

		if (!m_umComponentContainers.contains(sComponentType)) return nullptr;

		// Cast the pointer to the correct type and return
		return static_cast<ComponentContainer<T>*>(m_umComponentContainers[sComponentType]);
	}

	const std::vector<uint32_t>* getEntities() const { return &m_vEntities; }

protected:
private:
	template <typename T>
	ComponentContainer<T>* createComponentContainer()
	{
		// Get the components type as a string
		std::string sComponentType = typeid(T).name();

		ComponentContainer<T>* pContainer = new ComponentContainer<T>();

		m_umComponentContainers.insert(std::pair<std::string, IComponentContainer*>(sComponentType, pContainer));

		return pContainer;
	}
};