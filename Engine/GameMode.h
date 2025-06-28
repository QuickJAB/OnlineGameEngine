#pragma once

#include <vector>
#include <string>

class Controller;
class Entity;

class GameMode
{
public:
	GameMode() = default;
	~GameMode() = default;

	virtual void update(float in_dt);

	virtual void registerController(Controller* in_controller);
	void setControllerEntity(std::string in_controllerId, Entity* in_entity);

protected:
	std::vector<Controller*> m_controllers;
};

