#pragma once

#include "core/ECS/ECS.h"

class World
{
public:
	World();
	~World();

	virtual void update(float in_dt);

	template <typename T>
	T* getComponent(const uint32_t in_entity)
	{
		return m_ecs->getComponent<T>(in_entity);
	}

protected:
	ECS* m_ecs = nullptr;

private:
	
};