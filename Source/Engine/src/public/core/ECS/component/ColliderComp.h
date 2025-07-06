#pragma once

#include "ComponentBase.h"
#include "core/Delegates.h"

struct ColliderComp : public ComponentBase
{
	bool isStatic = true;

	Delegate<void()> onCollided;
};