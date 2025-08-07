#pragma once

class ECS;

struct TransformComp;
struct CollisionResult;

class CollisionSys
{
public:
protected:
private:
	ECS* const m_cpECS;

public:
	CollisionSys(ECS* const i_cpECS);

	void update(const float i_cfDt);
	void checkSpecificEntityCollisions(const uint32_t i_cuEntityId, const float i_cfDt);

	static void resolveBlockingCollision(const CollisionResult i_colRes,
		const float i_cfXDir, const float i_cfYDir, float& o_rfX, float& o_rfY);

protected:
private:
	static bool checkAABB(const TransformComp* const cpcA, const TransformComp* const cpcB);
};