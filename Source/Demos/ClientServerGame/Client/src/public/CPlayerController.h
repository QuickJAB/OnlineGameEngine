#pragma once

#include <core/game base/Controller.h>

class EventHandler;

class CPlayerController : public Controller
{
public:
protected:
private:
	EventHandler* m_pEventHandler;

public:
	CPlayerController(const uint32_t i_cuEntity, Level* i_pLevel, EventHandler* i_pEventHandler);
	~CPlayerController();

protected:
private:
	void onKeyStatesUpdated(const bool* i_cpKeyStates);
};