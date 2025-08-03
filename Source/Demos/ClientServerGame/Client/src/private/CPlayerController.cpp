#include "CPlayerController.h"

#include <input/EventHandler.h>
#include <core/ECS/Level.h>
#include <core/ECS/component/VelocityComp.h>
#include <core/ECS/component/ColliderComp.h>
#include <core/ECS/component/TransformComp.h>
#include <core/ECS/system/CollisionSys.h>
#include <JNet/JNetPeer.h>

#include <GGamePkts.h>

CPlayerController::CPlayerController(const uint32_t i_cuEntity, Level* const i_cpLevel, EventHandler* const i_cpEventHandler,
	JNet::JNetPeer* const i_cpServer) :
	Controller(i_cuEntity, i_cpLevel), m_cpEventHandler(i_cpEventHandler), m_cpServer(i_cpServer)
{
	m_cpEventHandler->m_muldOnKeyStatesUpdated.add(this, &CPlayerController::onKeyStatesUpdated);

	m_cpLevel->getComponent<VelocityComp>(m_cuEntity)->fSpeed = 0.5f;

	ColliderComp* const cpColliderComp = m_cpLevel->getComponent<ColliderComp>(m_cuEntity);
	cpColliderComp->unidOnCollided.bind(this, &CPlayerController::onCollided);
	cpColliderComp->bIsStatic = false;
}

CPlayerController::~CPlayerController()
{
	m_cpEventHandler->m_muldOnKeyStatesUpdated.unbindAllFromOwner(this);
	m_cpLevel->getComponent<ColliderComp>(m_cuEntity)->unidOnCollided.unbind();
}

void CPlayerController::onKeyStatesUpdated(const bool* i_cpKeyStates)
{
	VelocityComp* const cpVelocity = m_cpLevel->getComponent<VelocityComp>(m_cuEntity);

	cpVelocity->fXDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_D] - i_cpKeyStates[SDL_SCANCODE_A]);
	cpVelocity->fYDir = static_cast<float>(i_cpKeyStates[SDL_SCANCODE_S] - i_cpKeyStates[SDL_SCANCODE_W]);

	ClientInputPkt pkt;
	pkt.uPlayerID = m_cpServer->getConnectionID();
	pkt.buildMask(cpVelocity->fXDir, cpVelocity->fYDir, false);

	JNet::JNetOutPktData pktData;
	pktData.sData = pkt.serialize();

	m_cpServer->queueOutgoingPkt(pktData);
}

void CPlayerController::onCollided(const CollisionResult i_colRes)
{
	const VelocityComp* const cpcVel= m_cpLevel->getComponent<VelocityComp>(m_cuEntity);
	TransformComp* const cpTrans = m_cpLevel->getComponent<TransformComp>(m_cuEntity);

	CollisionSys::resolveBlockingCollision(i_colRes, cpcVel->fXDir, cpcVel->fYDir, cpTrans->fX, cpTrans->fY);
}
