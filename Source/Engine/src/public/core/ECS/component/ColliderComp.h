#pragma once

#include "ComponentBase.h"
#include "core/Delegates.h"

struct ColliderComp : public ComponentBase
{
	bool bIsStatic = true;

	Delegate<void()> unidOnCollided;
};