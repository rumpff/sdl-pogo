#include "GameLevelManager.h"

void GameLevelManager::Initalize()
{
	LevelManager::Initalize();

	m_GameplayManager = new GameplayManager();

	m_ObjectManager->CreateObject(new PlayerObject());
}

void GameLevelManager::Close()
{
	m_ObjectManager->Close(); delete m_ObjectManager;
	m_GameplayManager->Close(); delete m_GameplayManager;
	
}

void GameLevelManager::GameTick(double deltaTime)
{
	m_ObjectManager->GameTick(deltaTime);
}