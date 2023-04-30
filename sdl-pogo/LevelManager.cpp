#include "LevelManager.h"

void LevelManager::Initialize()
{
	m_ObjectManager = new ObjectManager();
	m_ObjectManager->Initialize();

	Manager::Initialize();
}

void LevelManager::Close()
{
	// de mazzel
}

void LevelManager::Tick(double deltaTime)
{
	// tick tock 
}

void LevelManager::Render(SDL_Renderer* renderer)
{
	m_ObjectManager->RenderObjects(renderer);
}