#include "core/game base/Controller.h"

void Controller::possess(const uint32_t in_entity)
{
	if (m_world == nullptr) return;

	m_entity = in_entity;
}
