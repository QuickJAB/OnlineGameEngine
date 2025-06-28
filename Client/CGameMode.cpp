#include "CGameMode.h"
#include "CPlayerController.h"

void CGameMode::update(float in_dt)
{
	__super::update(in_dt);
}

void CGameMode::registerController(Controller* in_controller)
{
	__super::registerController(in_controller);
	
	static_cast<CPlayerController*>(in_controller)->setEventHandler(m_eventHandler);
}
