#pragma once

#include <GameInstance.h>
#include <Window.h>
#include <Renderer.h>

class CliGameInstance : public GameInstance
{
public:
	CliGameInstance() = default;
	~CliGameInstance() = default;

	void update(float dt) override;
	bool init() override;
	void cleanup() override;

private:
	Window* m_window;
	Renderer* m_renderer;
};