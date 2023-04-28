#pragma once
#include "Manager.h"

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
};

