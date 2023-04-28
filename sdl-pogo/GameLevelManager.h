#pragma once
#include "LevelManager.h"

#include "GameplayManager.h"

class GameLevelManager :
    public LevelManager
{
public:
	virtual void Initalize();
	virtual void Close();

private:
	GameplayManager* m_GameplayManager;
};

