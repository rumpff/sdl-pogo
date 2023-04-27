#pragma once
#include "Manager.h"

// play sounds and music
class AudioManager : Manager
{
public:
	virtual void Initalize();
	virtual void Close();
};

