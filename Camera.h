#pragma once
#include <sstream>

#include <SDL.h>

#include "LevelManager.h"
#include "UI.h"

/// <summary>
/// Handles SDL window and rendering
/// </summary>
class Camera
{
public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	void Initialize();
	void Close();
	void Render(LevelManager* currentLevel, UI* ui);

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

