#pragma once

#include <GameInstance.h>

class GGameInstance : public GameInstance
{
public:
	GGameInstance() : GameInstance() {}
	~GGameInstance() {}

	virtual void update(float in_dt) override { __super::update(in_dt); };
	virtual bool init() override { return __super::init(); };
	virtual void cleanup() override { __super::cleanup(); };

protected:

};

