#pragma once

#include <atomic>

class GameInstance;

class Engine
{
public:
	Engine(std::atomic<bool>& in_running, float in_fixedTimeStep) : 
		m_running(in_running), m_fixedTimeStep(in_fixedTimeStep) {}
	~Engine() = default;

	bool init(GameInstance* in_gInst);
	void run();

private:
	// General
	std::atomic<bool>& m_running;
	float m_fixedTimeStep = 0.f;

	GameInstance* m_gInst = nullptr;

	void cleanup();
};

