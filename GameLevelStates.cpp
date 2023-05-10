#include "GameLevelStates.h"
#include "GameLevelManager.h"

void PreGameState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    m_Level->GetUI()->ChangeState(new PreGameUI());
}

void PreGameState::StateTick(double deltaTime)
{
    m_WarmupTimer += deltaTime;

    if (m_WarmupTimer > m_WarmupLength)
    {
        m_Level->ChangeState(new GameState);
        return;
    }
}

void GameState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    m_Level->TimeScale = 1;
    m_Level->Stats.LevelTime = 0;

    m_Level->GetUI()->ChangeState(new MidGameUI());
}

void GameState::StateTick(double deltaTime)
{
    m_Level->Stats.LevelTime += deltaTime;

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

    m->GetPlayer()->ChangeState(new PlayerLimpState());

    m_Level->TimeScale = 1;

    m_Level->GetUI()->ChangeState(new CompleteGameUI());
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

void EndGameState::StateExit()
{
    if (m_Level->Stats.FastestTime > m_Level->Stats.LevelTime)
        m_Level->Stats.FastestTime = m_Level->Stats.LevelTime;
}


void GameOverState::StateEnter(GameLevelManager* m)
{
    GameLevelState::StateEnter(m);

    m->GetPlayer()->ChangeState(new PlayerLimpState());
    m_Level->TimeScale = 1;

    m_Level->GetUI()->ChangeState(new FailedGameUI());
}

void GameOverState::StateTick(double deltaTime)
{
    m_ResetTimer += deltaTime;
    m_Level->TimeScale = SDL_clamp(Easing::EaseOutExpo(m_ResetTimer, 1, -1, m_ResetLength * 0.75f), 0, 1);

    m_Level->GetObjectManager()->GameTick(deltaTime * m_Level->TimeScale);
    m_Level->GetObjectManager()->PhysicsTick(m_Level->Gravity, deltaTime * m_Level->TimeScale);
    
    
    if(m_ResetTimer > m_ResetLength)
    {
        m_Level->ReLoad();
    }
}