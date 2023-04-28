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
	virtual void Initalize();
	virtual void Close();

protected:
	ObjectManager* m_ObjectManager;
};

