#include "graphics/Window.h"

#include <SDL3/SDL_init.h>
#include <print>

using namespace std;

Window::Window(string in_title, int in_width, int in_height)
{
	m_title = in_title;
	m_width = in_width;
	m_height = in_height;

	SDL_Init(SDL_INIT_VIDEO);
	m_wnd = SDL_CreateWindow(m_title.c_str(), m_width, m_height, SDL_WINDOW_VULKAN);
}

Window::~Window()
{
	SDL_DestroyWindow(m_wnd);
	m_wnd = nullptr;

	SDL_Quit();
}