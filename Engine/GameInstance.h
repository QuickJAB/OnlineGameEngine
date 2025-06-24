#pragma once

class GameInstance
{
public:
	GameInstance() = default;
	~GameInstance() = default;

	virtual void update(float dt) {}
	virtual void fixedUpdate(float dt) {}
	virtual bool init() { return true; }
	virtual void cleanup() {}
};

