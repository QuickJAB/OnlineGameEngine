#include "graphics/Window.h"

#include <SDL3/SDL_init.h>
#include <print>

using namespace std;

Window::Window(string i_sTitle, int i_iWidth, int i_iHeight)
{
	m_sTitle = i_sTitle;
	m_iWidth = i_iWidth;
	m_iHeight = i_iHeight;

	SDL_Init(SDL_INIT_VIDEO);
	m_pWnd = SDL_CreateWindow(m_sTitle.c_str(), m_iWidth, m_iHeight, SDL_WINDOW_VULKAN);
}

Window::~Window()
{
	SDL_DestroyWindow(m_pWnd);
	m_pWnd = nullptr;

	SDL_Quit();
}