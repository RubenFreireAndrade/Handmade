#pragma once
#include <Windows.h>
#include <string>
#include <SDL.h>
#include "Vector.h"

class Screen
{

public:

	static Screen* Instance();

	HWND GetWindowHandle();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	Vector<int> GetResolution();

	void SetMousePosition(int x, int y);
	void SetClearColor(Uint8 r, Uint8 g, Uint8 b);

	bool Initialize(const std::string& windowTitle,
		int width = 1024,
		int height = 768,
		bool fullscreen = false);

	void Clear();
	void Present();
	void Shutdown();

private:

	Screen();
	Screen(const Screen&);
	Screen& operator=(const Screen&);

	int m_width;
	int m_height;

	HWND m_windowHandle;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

};