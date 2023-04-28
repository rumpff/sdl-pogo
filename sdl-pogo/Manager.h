#pragma once

class Manager
{
public:
	/// <summary>
	/// Call when finishing initalization
	/// </summary>
	virtual void Initalize();
	virtual void Close();
	virtual bool IsInitialzed();

protected:
	bool m_IsInitalized = false;
};