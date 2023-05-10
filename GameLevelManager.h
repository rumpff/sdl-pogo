#pragma once
#include "LevelManager.h"

#include "GameLevelStates.h"
#include "GameplayManager.h"
#include "GameUI.h"
#include "GameStats.h"

class GameLevelManager :
    public LevelManager
{
public:
	GameStats Stats;
	float TimeScale;

	virtual void Initialize(Resources* resources);
	virtual void Close();
	virtual void ReLoad();
	virtual void Tick(double deltaTime);
	void ChangeState(GameLevelState* newState);
	PlayerObject* GetPlayer() { return m_Player; }
	GameUI* GetUI() { return (GameUI*)m_UI; }

	virtual void SpawnObjects(LevelData data);


private:
	PlayerObject* m_Player;
	GameLevelState* m_CurrentState;
	GameplayManager* m_GameplayManager;
};

