#pragma once

#include "core/ECS/ECS.h"

class Level
{
public:
protected:
	ECS* m_pECS = nullptr;

	std::unordered_map<uint32_t, uint32_t> m_umNetPlayerId;

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

	uint32_t getPlayerByNetworkId(const uint32_t i_uNetworkId);

protected:
private:
};