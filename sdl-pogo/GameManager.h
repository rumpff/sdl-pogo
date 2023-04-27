#pragma once
#include "Manager.h"

#include "LevelManager.h"
#include "AudioManager.h"
#include "ResourceLoader.h"

// handle window, control all managers, keep track of current level
class GameManager : public Manager
{
public:
	virtual void Initalize();
	virtual void Close();
	void ChangeLevel(LevelManager* newLevel);

private:
	LevelManager* m_CurrentLevel;
	ResourceLoader* m_ResourceLoader;
};