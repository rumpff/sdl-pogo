#pragma once
#include "UI.h"

#include "GameStats.h"
#include "GameUIStates.h"

class GameUI :
    public UI
{
public:
    virtual void Initialize(Resources* resources);
    virtual void Close();
    void Tick(GameStats stats, double deltaTime);
    virtual void Render(SDL_Renderer* renderer);
    void ChangeState(GameUIState* newState);

private:
    GameUIState* m_CurrentState;
};

