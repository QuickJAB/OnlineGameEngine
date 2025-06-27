#include "Window.h"
#include <SDL3/SDL_init.h>
#include <print>

using namespace std;

Window::Window(string in_title, int in_width, int in_height)
{
	m_title = in_title;
	m_width = in_width;
	m_height = in_height;
}

bool Window::init()
{
	// Init SDL, the window is the first thing in SDL that will be created so SDL is initalized here
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		println("ERROR: Failed to init SDL!");
		return false;
	}

	// Create a Vulkan window
	m_wnd = SDL_CreateWindow(m_title.c_str(), m_width, m_height, SDL_WINDOW_VULKAN);
	if (m_wnd == nullptr)
	{
		println("ERROR: Failed to create the SDL_Window!");
		return false;
	}

	return true;
}

void Window::cleanup()
{
	// Cleanip the SDL window
	SDL_DestroyWindow(m_wnd);
	m_wnd = nullptr;

	// Cleanup SDL since the window will be the last part of SDL to be destroyed in the application
	SDL_Quit();
}