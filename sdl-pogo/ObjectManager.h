#pragma once
#include "Manager.h"

#include <vector>

#include "GameObject.h"
#include "PlayerObject.h"
#include "GeometryObject.h"


/// <summary>
/// create and update objects, keep track of all objects, 
/// move objects that are not static and check for collisions
/// </summary>
class ObjectManager :
	public Manager
{
public:
	virtual void Initialize();
	virtual void Close();

	void GameTick(double deltaTime);
	void PhysicsTick(SDL_FPoint gravity, double deltaTime);
	void RenderObjects(SDL_Renderer* renderer);

	void CreateObject(GameObject* newObject);

private:
	std::vector<GameObject*> m_GameObjects;
	std::pair<bool, SDL_FPoint> IntersectCheck(std::pair<SDL_FPoint, SDL_FPoint> lineA, std::pair<SDL_FPoint, SDL_FPoint> lineB);
};

