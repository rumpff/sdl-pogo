#pragma once
#include "Manager.h"

#include <vector>

#include "GameObject.h"

/// <summary>
/// create and update objects, keep track of all objects, 
/// move objects that are not static and check for collisions
/// </summary>
class ObjectManager
{
public:
	ObjectManager();
	void Initalize();
	void Close();
	void GameTick(double deltaTime);

	void CreateObject(GameObject& newObject);

private:
	std::vector<GameObject> m_GameObjects;
};

