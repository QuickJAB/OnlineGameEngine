#pragma once

#include <cstdint>

class Level;
struct TransformComp;

class Controller
{
public:
protected:
	const uint32_t m_cuEntity;
	Level* const m_cpLevel;

private:

public:
	Controller(const uint32_t i_cuEntity, Level* const i_cpLevel);
	const TransformComp* const getTransformComp() const;

protected:
private:
};