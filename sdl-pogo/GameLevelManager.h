#pragma once
#include "LevelManager.h"

#include "GameplayManager.h"

class GameLevelManager :
    public LevelManager
{
public:
	virtual void Initalize();
	virtual void Close();
	virtual void GameTick(double deltaTime);

private:
	GameplayManager* m_GameplayManager;
	ObjectManager* m_ObjectManager;
};

