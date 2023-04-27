#include "GameManager.h"

void GameManager::Initalize()
{

}

void GameManager::Close()
{

}

void GameManager::ChangeLevel(LevelManager* newLevel)
{
	if (m_CurrentLevel != 0)
	{
		m_CurrentLevel->Close();
		delete m_CurrentLevel;
	}

	m_CurrentLevel = newLevel;
	m_CurrentLevel->Initalize(1);
}