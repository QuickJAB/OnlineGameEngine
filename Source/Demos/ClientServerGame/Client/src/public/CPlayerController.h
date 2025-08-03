#pragma once

#include <core/game base/Controller.h>

namespace JNet
{
	class JNetPeer;
}

class EventHandler;

struct CollisionResult;

class CPlayerController : public Controller
{
public:
protected:
private:
	EventHandler* const m_cpEventHandler;
	JNet::JNetPeer* const m_cpServer;

public:
	CPlayerController(const uint32_t i_cuEntity, Level* const i_cpLevel, EventHandler* const i_cpEventHandler,
		JNet::JNetPeer* const i_cpServer);
	~CPlayerController();

protected:
private:
	void onKeyStatesUpdated(const bool* i_cpKeyStates);
	void onCollided(const CollisionResult i_colRes);
};