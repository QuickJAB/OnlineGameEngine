#include "GGameState.h"

#include <core/ECS/component/TransformComp.h>
#include <core/game base/Controller.h>

#include "GGamePkts.h"

void GGameState::serializeGameState(std::string& o_rsData)
{
	GameStateUpdatePkt pkt;

	uint8_t entityNum = 0;
	for (auto pIt = m_umControllers.begin(); pIt != m_umControllers.end(); ++pIt)
	{
		const TransformComp* const cpcTransform = pIt->second->getTransformComp();
		pkt.entityData[entityNum].EntityID = cpcTransform->uOwner;
		pkt.entityData[entityNum].x = cpcTransform->fX;
		pkt.entityData[entityNum].y = cpcTransform->fY;
	}

	o_rsData = pkt.serialize();
}
