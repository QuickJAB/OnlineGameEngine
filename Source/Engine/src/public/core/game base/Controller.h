#pragma once

#include <cstdint>

class Level;

class Controller
{
public:
protected:
	const uint32_t m_cuEntity;
	Level* m_pLevel;

private:

public:
	Controller(const uint32_t i_cuEntity, Level* i_pLevel);

protected:
private:
};