#pragma once

#include <core/game base/GameInstance.h>

class GGameInstance : public GameInstance
{
public:
	GGameInstance() : GameInstance() {}
	~GGameInstance() {}

	virtual bool init() override;
	virtual void update(float in_dt) override;
	virtual void cleanup() override;

};
