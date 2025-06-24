#pragma once

#include <string>
#include <SDL3/SDL_video.h>

class Window
{
public:
	Window(std::string in_title, int in_width, int in_height);
	~Window() = default;

	bool init();
	void cleanup();

	SDL_Window* getSDLWindow() { return m_wnd; }

private:
	std::string m_title = "Game Window";
	int m_width = 800;
	int m_height = 600;

	SDL_Window* m_wnd = nullptr;
};