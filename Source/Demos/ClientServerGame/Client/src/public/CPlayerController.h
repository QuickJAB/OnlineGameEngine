#pragma once

#include <core/game base/Controller.h>

class EventHandler;

class CPlayerController : public Controller
{
public:
protected:
private:
	EventHandler* m_pEventHandler = nullptr;

public:
	CPlayerController(EventHandler* i_pEventHandler);
	~CPlayerController();

protected:
private:
	void onKeyStatesUpdated(const bool* i_cpKeyStates);
};