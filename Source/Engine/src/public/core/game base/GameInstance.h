#pragma once

class GameInstance
{
public:
	GameInstance() = default;
	~GameInstance() = default;

	virtual void update(float in_dt);

	bool isRunning() { return m_running; }

protected:


private:
	bool m_running = true;
};