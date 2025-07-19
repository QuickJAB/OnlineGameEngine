#include "graphics/Window.h"

#include <SDL3/SDL_init.h>

using namespace std;

SDL_Window* const Window::initAndCreateWindow(const string i_csTitle, const int i_ciWidth, const int i_ciHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	return SDL_CreateWindow(i_csTitle.c_str(), i_ciWidth, i_ciHeight, SDL_WINDOW_VULKAN);
}

Window::Window(const string i_csTitle, const int i_ciWidth, const int i_ciHeight) :
	m_cpWnd(initAndCreateWindow(i_csTitle, i_ciWidth, i_ciHeight))
{
}

Window::~Window()
{
	SDL_DestroyWindow(m_cpWnd);
	SDL_Quit();
}
