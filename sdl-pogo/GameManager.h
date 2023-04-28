#pragma once
#include "Manager.h"

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameLevelManager.h"
#include "AudioManager.h"
#include "ResourceLoader.h"

/// <summary>
/// handle window, control all managers, keep track of current level
/// </summary>
class GameManager : 
	public Manager
{
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	virtual void Initalize();
	virtual void Close();
	void ChangeLevel(LevelManager* newLevel);
	void Game();

private:
	SDL_Window* m_Window = 0;
	SDL_Surface* m_ScreenSurface = 0;
	SDL_Renderer* m_Renderer = 0;

	LevelManager* m_CurrentLevel = 0;
	AudioManager* m_AudioManager = 0;
	ResourceLoader* m_ResourceLoader = 0;
};