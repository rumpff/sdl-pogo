#pragma once

#include <SDL.h>
#include "Resources.h"

class Manager
{
public:
	/// <summary>
	/// Call when finishing initalization
	/// </summary>
	virtual void Initialize(Resources* resources);
	virtual void Close();
	virtual bool IsInitialzed();

protected:
	bool m_IsInitalized = false;
	Resources* m_Resources;
};