#include "GameUI.h"

void GameUI::Initialize(Resources* resources)
{
	Manager::Initialize(resources);
	ChangeState(new PreGameUI);
}

void GameUI::Close()
{
	delete m_CurrentState;
}

void GameUI::Tick(GameStats stats, double deltaTime)
{
	m_CurrentState->StateTick(stats, deltaTime);
}

void GameUI::Render(SDL_Renderer* renderer)
{
	m_CurrentState->StateRender(renderer);
}

void GameUI::ChangeState(GameUIState* newState)
{
	if (m_CurrentState != 0)
	{
		m_CurrentState->StateExit();
		delete m_CurrentState;
	}

	m_CurrentState = newState;
	m_CurrentState->StateEnter(this, m_Resources);
}