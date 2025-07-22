#pragma once

#include <core/game base/Controller.h>

class EventHandler;

struct CollisionResult;

class CPlayerController : public Controller
{
public:
protected:
private:
	EventHandler* const m_cpEventHandler;

public:
	CPlayerController(const uint32_t i_cuEntity, Level* const i_cpLevel, EventHandler* const i_cpEventHandler);
	~CPlayerController();

protected:
private:
	void onKeyStatesUpdated(const bool* i_cpKeyStates);
	void onCollided(const CollisionResult i_colRes);
};