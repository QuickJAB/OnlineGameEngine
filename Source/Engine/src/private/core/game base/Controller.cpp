#include "core/game base/Controller.h"

#include "core/ECS/Level.h"

Controller::Controller(const uint32_t i_cuEntity, Level* i_pLevel) :
	m_cuEntity(i_cuEntity), m_pLevel(i_pLevel)
{
}