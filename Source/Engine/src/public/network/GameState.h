#pragma once

#include <vector>

class Controller;

class GameState
{
public:
protected:
private:

public:
	GameState() = default;
	~GameState();

	void addController(Controller* const i_cpController);

protected:
	std::vector<Controller*> m_vControllers;

private:
};