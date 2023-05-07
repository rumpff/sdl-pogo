#include "GameLevelManager.h"

void GameLevelManager::Initialize()
{
	LevelManager::Initialize();

	m_GameplayManager = new GameplayManager();
}

void GameLevelManager::Close()
{
	m_ObjectManager->Close(); delete m_ObjectManager;
	m_GameplayManager->Close(); delete m_GameplayManager;
	
}

void GameLevelManager::Tick(double deltaTime)
{
	m_ObjectManager->GameTick(deltaTime);
	m_ObjectManager->PhysicsTick(Gravity, deltaTime);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_R])
	{
		ReLoad();
	}
}