#include "core/game base/Controller.h"

void Controller::possess(const uint32_t i_uEntity)
{
	if (m_pLevel == nullptr) return;

	m_uEntity = i_uEntity;
}
