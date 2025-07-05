#pragma once

#include <core/game base/World.h>

class MovementSys;

class GWorld : public World
{
public:
	GWorld();
	~GWorld();

	virtual void update(float in_dt) override;

private:
	MovementSys* m_movementSys = nullptr;
};