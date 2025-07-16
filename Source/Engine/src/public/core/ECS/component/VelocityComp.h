#pragma once

#include "ComponentBase.h"

struct VelocityComp : public ComponentBase
{
	float fXDir = 0;
	float fYDir = 0;
	float fSpeed = 0;
};