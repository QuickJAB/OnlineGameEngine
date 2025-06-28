#pragma once

#include <GameInstance.h>

class GGameInstance : public GameInstance
{
	virtual void update(float in_dt) override { __super::update(in_dt); }
	virtual void fixedUpdate(float in_dt) override { __super::fixedUpdate(in_dt); }
	virtual bool init() override { return __super::init(); }
	virtual void cleanup() override { __super::cleanup(); }
};

