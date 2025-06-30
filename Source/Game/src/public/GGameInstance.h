#pragma once

#include <core/game base/GameInstance.h>

class NetBase;

class GGameInstance : public GameInstance
{
public:
	GGameInstance() : GameInstance() {}
	~GGameInstance() {}

	virtual bool init() override;
	virtual void update(float in_dt) override;
	virtual void cleanup() override;

	void initNet(NetBase* in_net) { m_net = in_net; }

protected:
	NetBase* m_net = nullptr;
};
