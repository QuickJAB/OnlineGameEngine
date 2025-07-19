#include "graphics/Window.h"

#include <SDL3/SDL_init.h>

using namespace std;

Window::Window(const string i_csTitle, const int i_ciWidth, const int i_ciHeight) :
	m_sTitle(i_csTitle), m_iWidth(i_ciWidth), m_iHeight(i_ciHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	m_pWnd = SDL_CreateWindow(m_sTitle.c_str(), m_iWidth, m_iHeight, SDL_WINDOW_VULKAN);
}

Window::~Window()
{
	SDL_DestroyWindow(m_pWnd);
	m_pWnd = nullptr;

	SDL_Quit();
}