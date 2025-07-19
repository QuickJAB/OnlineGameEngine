#include "core/game base/Controller.h"

#include "core/ECS/Level.h"

Controller::Controller(const uint32_t i_cuEntity, Level* const i_cpLevel) :
	m_cuEntity(i_cuEntity), m_cpLevel(i_cpLevel)
{
}