#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

template <typename T>
class ComponentContainer
{
public:
	T* createComponent(const uint32_t& in_entityId)
	{
		// Early return if that entity already has this component
		if (map.contains(in_entityId)) return nullptr;

		// Construct the default component
		T component = T();

		// Add the component into the map
		map.insert(std::make_pair(in_entityId, component));

		// Add the pointer to the components vector
		components.push_back(&map.at(in_entityId));

		// Return the components address within the map
		return &component;
	}

	void destroyComponent(const uint32_t& in_entityId)
	{
		// Early return of the entity doesn't have this component
		if (!map.contains(in_entityId)) return;

		// Remove the component from the vector
		components.erase(map.at(in_entityId));

		// Remove the entity's component from the map
		map.erase(in_entityId);
	}

	const size_t& getSize() const { return components.size(); }

	const std::vector<T*>* getComponents() const { return &components; }

private:
	// The true source of the container
	std::unordered_map<uint32_t, T> map;

	// Pointers to the components that can be used by systems to quickly itterate over all components
	std::vector<T*> components;
};