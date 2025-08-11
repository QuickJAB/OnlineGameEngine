#pragma once

#include <core/ECS/component/ComponentBase.h>

struct GCombatComponent : public ComponentBase
{
	float uHealth = 0;
	float uMaxHealth = 0;
	float uDamage = 0;
};