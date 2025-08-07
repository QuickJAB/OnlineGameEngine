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
	void moveSpecificEntity(const uint32_t i_cuEntityId, const float i_cfDt);
	void checkSpecificEntityCollisions(const uint32_t i_cuEntityId, const float i_cfDt);

	virtual void load() override;

protected:
private:
};