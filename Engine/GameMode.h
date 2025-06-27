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

	void update(float in_dt, const bool* in_keyStates);

	void registerController(Controller* in_controller);

	void setControllerEntity(std::string in_controllerId, Entity* in_entity);

private:
	std::vector<Controller*> m_controllers;
};

