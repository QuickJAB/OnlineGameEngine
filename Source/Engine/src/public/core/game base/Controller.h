#pragma once

#include <string>

class Entity;

class Controller
{
public:
	Controller(std::string in_id) : m_id(in_id) {}
	~Controller() = default;

	virtual void update(float in_dt) {}
	void posses(Entity* in_entity) { m_entity = in_entity; }

	std::string getId() const { return m_id; }

protected:
	Entity* m_entity = nullptr;
	std::string m_id;
};

