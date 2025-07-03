#pragma once

#include "ECS/component/ComponentBase.h"

struct TransformComp : public ComponentBase
{
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
};