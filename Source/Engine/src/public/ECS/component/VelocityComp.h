#pragma once

#include "ECS/component/ComponentBase.h"

struct VelocityComp : public ComponentBase
{
	float xDir = 0;
	float yDir = 0;
	float speed = 0;
};