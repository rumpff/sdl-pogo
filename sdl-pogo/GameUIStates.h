#pragma once

#include <SDL.h>
#include "GameStats.h"
#include "Label.h"
#include "Camera.h"
#include "SimpleEasing.h"
class Resources;
class GameUI;
class GameUIState
{
public:
    virtual void StateEnter(GameUI* m, Resources* r) { m_UI = m; m_Resources = r; }
    virtual void StateTick(GameStats stats, double deltaTime) { }
    virtual void StateRender(SDL_Renderer* renderer) {  }
    virtual void StateExit() { }

protected:
    GameUI* m_UI;
    Resources* m_Resources;
};

class PreGameUI : public GameUIState
{
public:
    virtual void StateEnter(GameUI* m, Resources* r);
    virtual void StateExit();
    virtual void StateTick(GameStats stats, double deltaTime);
    virtual void StateRender(SDL_Renderer* renderer);

private:
    Label* m_CountdownLabel;
    float m_StateTimer;
    float m_StateDuration = 1;
};

class MidGameUI : public GameUIState
{
public:
    virtual void StateEnter(GameUI* m, Resources* r);
    virtual void StateExit();
    virtual void StateTick(GameStats stats, double deltaTime);
    virtual void StateRender(SDL_Renderer* renderer);

private: 
    Label* m_TimerLabel;
};

class CompleteGameUI : public GameUIState
{
public:
    virtual void StateEnter(GameUI* m, Resources* r);
    virtual void StateExit();
    virtual void StateTick(GameStats stats, double deltaTime);
    virtual void StateRender(SDL_Renderer* renderer);

private:
    float m_StateTimer;
    Label* m_TimeLabel;
    Label* m_PBLabel;
};

class FailedGameUI : public GameUIState
{
public:
    virtual void StateEnter(GameUI* m, Resources* r);
    virtual void StateExit();
    virtual void StateTick(GameStats stats, double deltaTime);
    virtual void StateRender(SDL_Renderer* renderer);

private:
    float m_ResetTimer = 0;
    float m_ResetLength = 1.5;

    Label* m_DeathLabel;
};