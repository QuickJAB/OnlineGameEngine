#pragma once

class ECS;

struct TransformComp;

class CollisionSys
{
public:
protected:
private:
	ECS* const m_cpECS = nullptr;

public:
	CollisionSys(ECS* const i_cpECS);
	~CollisionSys() = default;

	void update(const float i_cfDt);

protected:
private:
	bool checkAABB(const TransformComp* cpA, const TransformComp* cpB);
};