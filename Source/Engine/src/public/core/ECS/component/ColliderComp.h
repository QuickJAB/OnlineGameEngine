#pragma once

#include "ComponentBase.h"

struct ColliderComp : public ComponentBase
{
	bool isStatic = true;
};