#pragma once

class World;
class GameMode;

class GameInstance
{
public:
	GameInstance() = default;
	~GameInstance() = default;

	virtual void update(float in_dt) {}
	virtual void fixedUpdate(float in_dt) {}
	virtual bool init() { return true; }
	virtual void cleanup() {}

	bool shouldQuit() { return m_shouldQuit; }

protected:
	bool m_shouldQuit = false;

	World* m_world = nullptr;
	GameMode* m_gameMode = nullptr;
};

