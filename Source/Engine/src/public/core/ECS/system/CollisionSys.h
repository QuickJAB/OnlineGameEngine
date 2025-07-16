#pragma once

class ECS;

struct TransformComp;

class CollisionSys
{
public:
protected:
private:
	ECS* m_pECS = nullptr;

public:
	CollisionSys(ECS* i_pECS);
	~CollisionSys() = default;

	void update(float i_fDt);

protected:
private:
	bool checkAABB(const TransformComp* cpA, const TransformComp* cpB);
};