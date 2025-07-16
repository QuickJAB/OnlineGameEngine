#pragma once

#include <string>
#include <SDL3/SDL_video.h>

class Window
{
public:
protected:
private:
	std::string m_sTitle = "Game Window";
	int m_iWidth = 800;
	int m_iHeight = 600;

	SDL_Window* m_pWnd = nullptr;

public:
	Window(std::string i_sTitle, int i_iWidth, int i_iHeight);
	~Window();

	SDL_Window* getSDLWindow() { return m_pWnd; }

protected:
private:
};