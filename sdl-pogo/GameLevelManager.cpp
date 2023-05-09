#include "GameLevelManager.h"

void GameLevelManager::Initialize(Resources* resources)
{
	LevelManager::Initialize(resources);

	m_UI = new GameUI();
	m_UI->Initialize(resources);

	ChangeState(new PreGameState());
}

void GameLevelManager::ReLoad()
{
	LevelManager::ReLoad();
	ChangeState(new PreGameState());
}

void GameLevelManager::Close()
{
	LevelManager::Close();

	delete m_CurrentState;
}

void GameLevelManager::Tick(double deltaTime)
{
	m_CurrentState->StateTick(deltaTime);
	GetUI()->Tick(Stats, deltaTime);

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