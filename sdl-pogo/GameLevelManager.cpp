#include "GameLevelManager.h"

void GameLevelManager::Initialize()
{
	LevelManager::Initialize();

	m_GameplayManager = new GameplayManager();	
	ChangeState(new PreGameState());
}

void GameLevelManager::ReLoad()
{
	LevelManager::ReLoad();
	ChangeState(new PreGameState());
}

void GameLevelManager::Close()
{
	m_ObjectManager->Close(); delete m_ObjectManager;
	m_GameplayManager->Close(); delete m_GameplayManager;
	
}

void GameLevelManager::Tick(double deltaTime)
{
	m_CurrentState->StateTick(deltaTime);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_R])
	{
		ReLoad();
	}
}

void GameLevelManager::SpawnObjects(LevelData data)
{
	LevelManager::SpawnObjects(data);

	std::vector<GameObject*> objects = m_ObjectManager->GetObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->Type == Player)
		{
			m_Player = (PlayerObject*)objects[i];
		}
	}
}

void GameLevelManager::ChangeState(GameLevelState* newState)
{
	if (m_CurrentState != 0)
	{
		m_CurrentState->StateExit();
		delete m_CurrentState;
	}

	m_CurrentState = newState;
	m_CurrentState->StateEnter(this);
}