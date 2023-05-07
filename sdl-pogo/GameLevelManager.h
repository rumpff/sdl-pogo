#pragma once
#include "LevelManager.h"

#include "GameLevelStates.h"
#include "GameplayManager.h"

class GameLevelManager :
    public LevelManager
{
public:
	virtual void Initialize();
	virtual void Close();
	virtual void ReLoad();
	virtual void Tick(double deltaTime);
	void ChangeState(GameLevelState* newState);
	PlayerObject* GetPlayer() { return m_Player; }

	virtual void SpawnObjects(LevelData data);

	float TimeScale;
	float LevelTime;

public:
	PlayerObject* m_Player;
	GameLevelState* m_CurrentState;
	GameplayManager* m_GameplayManager;
};

