#pragma once
#include "Manager.h"

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Camera.h"
#include "GameLevelManager.h"
#include "AudioManager.h"
#include "Resources.h"

/// <summary>
/// handle window, control all managers, keep track of current level
/// </summary>
class GameManager : 
	public Manager
{

public:
	virtual void Initialize();
	virtual void Close();
	LevelManager* ChangeLevel(LevelManager* newLevel);
	LevelManager* ChangeLevel(LevelManager* newLevel, LevelData data);
	void Game();

	LevelManager* GetLevel() { return m_CurrentLevel; }
	AudioManager* GetAudio() { return m_AudioManager; }

private:
	Camera* m_Camera = 0;
	LevelManager* m_CurrentLevel = 0;
	AudioManager* m_AudioManager = 0;
};