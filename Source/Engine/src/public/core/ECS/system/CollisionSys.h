#pragma once

class ECS;

struct TransformComp;

class CollisionSys
{
public:
	CollisionSys(ECS* in_ecs);
	~CollisionSys() = default;

	void update(float in_dt);

private:
	ECS* m_ecs = nullptr;

	bool checkAABB(const TransformComp* a, const TransformComp* b);
};