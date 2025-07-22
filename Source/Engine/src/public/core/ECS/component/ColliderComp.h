#pragma once

#include "ComponentBase.h"
#include "core/Delegates.h"

struct CollisionResult
{
	const float cfXOverlap;
	const float cfYOverlap;
};

struct ColliderComp : public ComponentBase
{
	bool bIsStatic = true;

	Delegate<void(const CollisionResult)> unidOnCollided;
};