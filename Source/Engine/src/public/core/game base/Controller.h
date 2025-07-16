#pragma once

#include <cstdint>

class Level;

class Controller
{
public:
protected:
	uint32_t m_uEntity = (uint32_t)-1;

	Level* m_pLevel = nullptr;

private:

public:
	Controller() = default;

	void setLevel(Level* i_pLevel) { m_pLevel = i_pLevel; }

	void possess(const uint32_t i_uEntity);
	void depossess() { m_uEntity = (uint32_t)-1; }

protected:
private:
};