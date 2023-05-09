#pragma once
#include "Manager.h"

#include <SDL.h>

#include "LevelData.h"
#include "ObjectManager.h"
#include "UI.h"

/// <summary>
/// handle level loading, unloading, restarting
/// </summary>
class LevelManager : 
	public Manager
{
public:
	SDL_FPoint Gravity { 0, 1500.0f  };

	virtual void Initialize(Resources* resources);
	virtual void Close();
	virtual void ReLoad();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	void LoadData(LevelData data);
	virtual void SpawnObjects(LevelData data);

	LevelData GetLevelData() { m_LevelData; }
	ObjectManager* GetObjectManager() { return m_ObjectManager; }
	UI* GetUI() { return m_UI; }

protected:
	LevelData m_LevelData;
	ObjectManager* m_ObjectManager;
	UI* m_UI;
};

