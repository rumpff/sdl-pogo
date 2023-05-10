#include "Manager.h"

void Manager::Initialize(Resources* resources)
{
	m_IsInitalized = true;
	m_Resources = resources;
}

void Manager::Close()
{
	// Houdoe
}

bool Manager::IsInitialzed()
{
	return m_IsInitalized;
}