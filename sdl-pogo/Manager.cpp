#include "Manager.h"

void Manager::Initalize()
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