#pragma once

#include <cstdint>

class World;

class Controller
{
public:
	Controller() = default;

	void setWorld(World* in_world) { m_world = in_world; }

	void possess(const uint32_t in_entity);
	void depossess() { m_entity = (uint32_t)-1; }

protected:
	uint32_t m_entity = (uint32_t)-1;

	World* m_world = nullptr;

private:

};