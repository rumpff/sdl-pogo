#pragma once
#include "Manager.h"

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "LevelManager.h"
#include "AudioManager.h"
#include "ResourceLoader.h"

// handle window, control all managers, keep track of current level
class GameManager : public Manager
{
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	virtual void Initalize();
	virtual void Close();
	void ChangeLevel(LevelManager* newLevel);
	void GameLoop();

private:
	SDL_Window* m_Window;
	SDL_Surface* m_ScreenSurface;
	SDL_Renderer* m_Renderer;

	LevelManager* m_CurrentLevel;
	AudioManager* m_AudioManager;
	ResourceLoader* m_ResourceLoader;
};