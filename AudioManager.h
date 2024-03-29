#pragma once
#include "Manager.h"

/// <summary>
/// play sounds and music
/// </summary>
class AudioManager : 
	public Manager
{
public:
	virtual void Initialize();
	virtual void Close();
};

