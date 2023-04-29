#include "GameLevelManager.h"

void GameLevelManager::Initalize()
{
	m_ObjectManager = new ObjectManager();
	m_GameplayManager = new GameplayManager();


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