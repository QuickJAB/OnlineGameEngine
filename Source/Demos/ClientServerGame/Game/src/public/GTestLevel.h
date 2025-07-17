#pragma once

#include <core/ECS/Level.h>

class MovementSys;
class CollisionSys;

class GTestLevel : public Level
{
public:
protected:
	MovementSys* m_pMovementSys = nullptr;
	CollisionSys* m_pCollisionSys = nullptr;

private:

public:
	GTestLevel();
	~GTestLevel();

	virtual void update(float i_fDt) override;

	virtual void load() override;
	virtual uint32_t spawnPlayer(float i_fX, float i_fY, bool i_bIsAlly);

protected:
private:
};