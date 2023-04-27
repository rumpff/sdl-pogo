#pragma once
#include "Manager.h"

// Handle gamelevel state, keep track of stats, look after player
class GameplayManager : Manager
{
public:
	virtual void Initalize();
	virtual void Close();
};

