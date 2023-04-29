#include "LevelManager.h"

void LevelManager::Initalize()
{
	m_ObjectManager = new ObjectManager();
}

void LevelManager::Close()
{
	// de mazzel
}

void LevelManager::GameTick(double deltaTime)
{
	// tick tock 
}

void LevelManager::Render(SDL_Renderer* renderer)
{
	m_ObjectManager->RenderObjects(renderer);
}