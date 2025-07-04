#pragma once

class ECS;

class World
{
public:
	World();
	~World();

	virtual void update(float in_dt);

protected:


private:
	ECS* m_ecs = nullptr;
};