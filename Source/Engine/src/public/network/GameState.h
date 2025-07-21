#pragma once

#include <unordered_map>

class Controller;

class GameState
{
public:
protected:
private:

public:
	GameState() = default;
	~GameState();

	Controller* const getController(const uint32_t i_cuEntityId);

protected:
	std::unordered_map<uint32_t, Controller*> m_umControllers;

private:
};