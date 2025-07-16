#pragma once

#include <core/ECS/Level.h>

class MovementSys;
class CollisionSys;

class GTestLevel : public Level
{
public:
	GTestLevel();
	~GTestLevel();

	virtual void update(float in_dt) override;

	virtual void load() override;

protected:
	MovementSys* m_movementSys = nullptr;
	CollisionSys* m_collisionSys = nullptr;
};