#include <SDL_syswm.h>
#include "Screen.h"
#include "Utility.h"

//======================================================================================================
Screen* Screen::Instance()
{
	static Screen* screenObject = new Screen();
	return screenObject;
}
//======================================================================================================
HWND Screen::GetWindowHandle()
{
	return m_windowHandle;
}
//======================================================================================================
SDL_Window* Screen::GetWindow()
{
	return m_window;
}
//======================================================================================================
SDL_Renderer* Screen::GetRenderer()
{
	return m_renderer;
}
//======================================================================================================
SDL_Point Screen::GetResolution()
{
	return SDL_Point{ m_width, m_height };
}
//======================================================================================================
void Screen::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(m_window, x, y);
}
//======================================================================================================
void Screen::SetClearColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
}
//======================================================================================================
bool Screen::Initialize(const std::string& windowTitle, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error initializing SDL.", Utility::Severity::Failure);
		return false;
	}

	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

	m_window = SDL_CreateWindow(windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height, screenFlag);

	if (!m_window)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Game window could not be created.", Utility::Severity::Failure);
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_renderer)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Renderer could not be created.", Utility::Severity::Failure);
		return false;
	}

	//Use this to get Windows handle on game window for
	//use with Windows message boxes and other stuff 
	SDL_SysWMinfo systemInfo;
	SDL_VERSION(&systemInfo.version);
	SDL_GetWindowWMInfo(m_window, &systemInfo);
	m_windowHandle = systemInfo.info.win.window;

	m_width = width;
	m_height = height;

	return true;
}
//======================================================================================================
void Screen::Clear()
{
	SDL_RenderClear(m_renderer);
}
//======================================================================================================
void Screen::Present()
{
	SDL_RenderPresent(m_renderer);
}
//======================================================================================================
void Screen::Shutdown()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}