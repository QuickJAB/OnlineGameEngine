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
	Window(const std::string i_csTitle, const int i_ciWidth, const int i_ciHeight);
	~Window();

	SDL_Window* const getSDLWindow() { return m_pWnd; }

protected:
private:
};