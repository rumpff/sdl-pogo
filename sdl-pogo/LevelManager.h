#pragma once
#include "Manager.h"

// handle level loading, unloading, restarting
class LevelManager : Manager
{
public:
	virtual void Initalize();
	virtual void Initalize(int x); // override with 
	virtual void Close();
};

