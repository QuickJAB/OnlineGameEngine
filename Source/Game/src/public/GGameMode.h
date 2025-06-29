#pragma once

#include <core/game base/GameMode.h>

class GGameMode : public GameMode
{
public:
	GGameMode() : GameMode() {}
	~GGameMode() = default;

	virtual void update(float in_dt) override;
};

