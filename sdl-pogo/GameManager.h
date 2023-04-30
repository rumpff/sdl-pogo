#pragma once
#include "Manager.h"

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Camera.h"
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
	virtual void Initialize();
	virtual void Close();
	void ChangeLevel(LevelManager* newLevel);
	void Game();

private:
	Camera* m_Camera = 0;
	LevelManager* m_CurrentLevel = 0;
	AudioManager* m_AudioManager = 0;
	ResourceLoader* m_ResourceLoader = 0;
};