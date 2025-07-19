#pragma once

#include "core/ECS/ECS.h"

class Level
{
public:
protected:
	ECS* const m_cpECS;

	std::unordered_map<uint32_t, uint32_t> m_umNetPlayerId;

private:

public:
	Level();
	~Level();

	virtual void update(const float i_cfDt) = 0;
	virtual void load() = 0;

	template <typename T>
	T* const getComponent(const uint32_t i_uEntity)
	{
		return m_cpECS->getComponent<T>(i_uEntity);
	}

	const uint32_t getPlayerByNetworkId(const uint32_t i_cuNetworkId);

protected:
private:
};