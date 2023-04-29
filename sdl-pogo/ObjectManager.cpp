#include "ObjectManager.h"

void ObjectManager::Initalize()
{
	// hello
}

void ObjectManager::Close()
{
	// Later he
}

void ObjectManager::CreateObject(GameObject* newObject)
{
	m_GameObjects.push_back(newObject);
}

void ObjectManager::GameTick(double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->GameTick(deltaTime);
	}
}
void ObjectManager::RenderObjects(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Render(renderer);
	}
}