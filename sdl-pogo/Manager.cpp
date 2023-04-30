#include "Manager.h"

void Manager::Initialize()
{
	m_IsInitalized = true;
}

void Manager::Close()
{
	// Houdoe
}

bool Manager::IsInitialzed()
{
	return m_IsInitalized;
}