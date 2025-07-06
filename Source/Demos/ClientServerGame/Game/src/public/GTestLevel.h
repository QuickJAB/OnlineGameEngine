#pragma once

#include <core/ECS/Level.h>

class MovementSys;

class GTestLevel : public Level
{
public:
	GTestLevel();
	~GTestLevel();

	virtual void update(float in_dt) override;

protected:
	MovementSys* m_movementSys = nullptr;
	
	virtual void load() override;
};