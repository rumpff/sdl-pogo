#pragma once
#include <sstream>

#include <SDL.h>

class Camera
{
public:
	void Initialize();
	void Close();

	SDL_Window* GetWindow() {
		return m_Window;
	}

	SDL_Surface* GetScreenSurface() {
		return m_ScreenSurface;
	}

	SDL_Renderer* GetRenderer() {
		return m_Renderer;
	}

private:
	SDL_Window* m_Window = 0;
	SDL_Surface* m_ScreenSurface = 0;
	SDL_Renderer* m_Renderer = 0;
};
