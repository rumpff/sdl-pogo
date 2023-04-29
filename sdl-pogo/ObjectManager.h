#pragma once
#include "Manager.h"

#include <vector>

#include "GameObject.h"
#include "PlayerObject.h"

/// <summary>
/// create and update objects, keep track of all objects, 
/// move objects that are not static and check for collisions
/// </summary>
class ObjectManager :
	public Manager
{
public:
	virtual void Initalize();
	virtual void Close();

	void GameTick(double deltaTime);
	void RenderObjects(SDL_Renderer* renderer);

	void CreateObject(GameObject* newObject);

private:
	std::vector<GameObject*> m_GameObjects;
};

