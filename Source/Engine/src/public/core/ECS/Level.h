#pragma once

#include "core/ECS/ECS.h"

class Level
{
public:
protected:
	ECS* m_pECS = nullptr;

private:

public:
	Level();
	~Level();

	virtual void update(float i_fDt);
	virtual void load();

	template <typename T>
	T* getComponent(const uint32_t i_uEntity)
	{
		return m_pECS->getComponent<T>(i_uEntity);
	}

protected:
private:
};