#pragma once

#include <vector>

#include "ECS/component/TransformComp.h"
#include "ComponentContainer.h"

class World
{
public:
	World() = default;
	~World() = default;

	const uint32_t createEntity();

	void update(float in_dt);

	// Components controlled by the world
	ComponentContainer<TransformComp> m_transformComps;

private:
	// The next unique id that will be used for the next spawned entity
	uint32_t m_nextEntityId = 0;
};