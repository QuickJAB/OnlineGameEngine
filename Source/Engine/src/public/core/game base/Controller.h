#pragma once

#include <cstdint>

class Level;

class Controller
{
public:
	Controller() = default;

	void setWorld(Level* in_world) { m_level = in_world; }

	void possess(const uint32_t in_entity);
	void depossess() { m_entity = (uint32_t)-1; }

protected:
	uint32_t m_entity = (uint32_t)-1;

	Level* m_level = nullptr;

private:

};