#include "GameMode.h"

#include "Controller.h"

using namespace std;

void GameMode::update(float in_dt)
{
	for (Controller* controller : m_controllers)
	{
		controller->update(in_dt);
	}
}

void GameMode::registerController(Controller* in_controller)
{
	m_controllers.push_back(in_controller);
}

void GameMode::setControllerEntity(string in_controllerId, Entity* in_entity)
{
	for (Controller* controller : m_controllers)
	{
		if (controller->getId() == in_controllerId)
		{
			controller->posses(in_entity);
			return;
		}
	}
}
