#pragma once

#include <core/ECS/Level.h>

class MovementSys;
class CollisionSys;

class GTestLevel : public Level
{
public:
protected:
	MovementSys* const m_cpMovementSys;
	CollisionSys* const m_cpCollisionSys;

private:

public:
	GTestLevel();
	~GTestLevel();

	virtual void update(const float i_cfDt) override;

	virtual void load() override;

protected:
private:
};