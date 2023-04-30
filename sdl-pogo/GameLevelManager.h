#pragma once
#include "LevelManager.h"

#include "GameplayManager.h"

class GameLevelManager :
    public LevelManager
{
public:
	virtual void Initialize();
	virtual void Close();
	virtual void Tick(double deltaTime);

private:
	GameplayManager* m_GameplayManager;
};

