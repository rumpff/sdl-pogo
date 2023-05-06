#pragma once
#include "Manager.h"

#include "ObjectManager.h"

/// <summary>
/// handle level loading, unloading, restarting
/// </summary>
class LevelManager : 
	public Manager
{
public:
	SDL_FPoint Gravity{ 0, 1500.0f  };

	virtual void Initialize();
	virtual void Close();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);

protected:
	ObjectManager* m_ObjectManager;
};

