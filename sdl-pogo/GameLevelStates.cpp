#include "GameLevelStates.h"
#include "GameLevelManager.h"



void PreGameState::StateTick(double deltaTime)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    for (size_t i = 0; i < (size_t)SDL_NUM_SCANCODES; i++)
    {
        if (currentKeyStates[(SDL_Scancode)i])
        {
            m_Level->ChangeState(new GameState);
            break;
        }
    }

}

void GameState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    m_Level->TimeScale = 1;
    m_Level->LevelTime = 0;
}

void GameState::StateTick(double deltaTime)
{
    m_Level->LevelTime += deltaTime;

	m_Level->GetObjectManager()->GameTick(deltaTime * m_Level->TimeScale);
	m_Level->GetObjectManager()->PhysicsTick(m_Level->Gravity, deltaTime * m_Level->TimeScale);


    // Check player flags
    if (m_Level->GetPlayer()->Finished)
    {
        m_Level->ChangeState(new EndGameState());
        return;
    }

    if (m_Level->GetPlayer()->Dead)
    {
        m_Level->ChangeState(new GameOverState());
        return;
    }
}


void EndGameState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    printf("time: ");
    printf(std::to_string(m_Level->LevelTime).c_str());

    m->GetPlayer()->ChangeState(new PlayerLimpState());

    m_Level->TimeScale = 1;
}

void EndGameState::StateTick(double deltaTime)
{
    m_Level->GetObjectManager()->GameTick(deltaTime * m_Level->TimeScale);
    m_Level->GetObjectManager()->PhysicsTick(m_Level->Gravity, deltaTime * m_Level->TimeScale);

    if (m_Level->TimeScale > 0.05)
    {
        m_Level->TimeScale *= (1 - deltaTime * 2);
        SDL_clamp(m_Level->TimeScale, 0.05, 1);
    }
}



void GameOverState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    m->GetPlayer()->ChangeState(new PlayerLimpState());
    m_Level->TimeScale = 1;
}

void GameOverState::StateTick(double deltaTime)
{
    m_Level->GetObjectManager()->GameTick(deltaTime * m_Level->TimeScale);
    m_Level->GetObjectManager()->PhysicsTick(m_Level->Gravity, deltaTime * m_Level->TimeScale);

    if (m_Level->TimeScale > 0.05)
    {
        m_Level->TimeScale *= (1 - deltaTime * 2);
        SDL_clamp(m_Level->TimeScale, 0.05, 1);
    }
    else
    {
        m_Level->ReLoad();
    }
}