#pragma once
#include "Manager.h"

// create and update objects, keep track of all objects, 
// move objects that are not static and check for collisions
class ObjectManager : Manager
{
public:
	virtual void Initalize();
	virtual void Close();
};

