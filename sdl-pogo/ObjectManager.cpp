#include "ObjectManager.h"

void ObjectManager::Initialize()
{
	// heyy
	CreateObject(new PlayerObject());
}

void ObjectManager::Close()
{
	// Later he
}

void ObjectManager::CreateObject(GameObject* newObject)
{
	m_GameObjects.push_back(newObject);
	newObject->OnCreate();
}

void ObjectManager::GameTick(double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Tick(deltaTime);
	}
}

void ObjectManager::PhysicsTick(SDL_FPoint gravity, double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* object = m_GameObjects[i];

		if (!object->HandlePhysics)
			continue;
		
		SDL_FPoint velocity = object->Velocity;

		// Modify Velocities
		velocity.x += gravity.x;
		velocity.y += gravity.y;

		// Apply Velocities
		object->Velocity = velocity;

		// Move Object
		object->Position.x += object->Velocity.x;
		object->Position.y += object->Velocity.y;

		// Check for collision
	}
}

void ObjectManager::RenderObjects(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Render(renderer);
	}
}