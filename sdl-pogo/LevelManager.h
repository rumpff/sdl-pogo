#pragma once
#include "Manager.h"

#include <SDL.h>

#include "LevelData.h"
#include "ObjectManager.h"

/// <summary>
/// handle level loading, unloading, restarting
/// </summary>
class LevelManager : 
	public Manager
{
public:
	SDL_FPoint Gravity { 0, 1500.0f  };

	virtual void Initialize();
	virtual void Close();
	virtual void ReLoad();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	void LoadData(LevelData data);
	void SpawnObjects(LevelData data);

protected:
	LevelData m_LevelData;
	ObjectManager* m_ObjectManager;
};

