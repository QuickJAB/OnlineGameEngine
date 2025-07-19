#pragma once

#include <string>
#include <SDL3/SDL_video.h>

class Window
{
public:
protected:
private:
	SDL_Window* const m_cpWnd;

public:
	Window(const std::string i_csTitle, const int i_ciWidth, const int i_ciHeight);
	~Window();

	SDL_Window* const getSDLWindow() { return m_cpWnd; }

protected:
private:
	static SDL_Window* const initAndCreateWindow(const std::string i_csTitle, const int i_ciWidth, const int i_ciHeight);
};