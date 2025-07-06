#pragma once

#include "core/ECS/ECS.h"

class Level
{
public:
	Level();
	~Level();

	virtual void update(float in_dt);
	virtual void load();

	template <typename T>
	T* getComponent(const uint32_t in_entity)
	{
		return m_ecs->getComponent<T>(in_entity);
	}

protected:
	ECS* m_ecs = nullptr;

private:
	
};