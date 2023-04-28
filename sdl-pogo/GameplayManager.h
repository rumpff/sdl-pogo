#pragma once
#include "Manager.h"

/// <summary>
/// Handle gamelevel state, keep track of stats, look after player
/// </summary>
class GameplayManager : 
	public Manager
{
public:
	virtual void Initalize();
	virtual void Close();
};

