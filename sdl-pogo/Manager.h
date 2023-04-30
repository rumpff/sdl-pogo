#pragma once
#include <SDL.h>

class Manager
{
public:
	/// <summary>
	/// Call when finishing initalization
	/// </summary>
	virtual void Initialize();
	virtual void Close();
	virtual bool IsInitialzed();

protected:
	bool m_IsInitalized = false;
};