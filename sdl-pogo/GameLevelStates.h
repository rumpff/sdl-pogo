#pragma once

#include <SDL.h>

#include "GameUIStates.h"
#include "SimpleEasing.h"

class GameLevelManager;
class GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m) { m_Level = m; }
    virtual void StateTick(double deltaTime) { }
    virtual void StateExit() { }

protected:
    GameLevelManager* m_Level;
};

class PreGameState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    //virtual void StateExit();

private:
    float m_WarmupTimer = 0;
    float m_WarmupLength = 1;
};

class GameState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    //virtual void StateExit();
};

class EndGameState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();
};

class GameOverState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    //virtual void StateExit();

private: 
    float m_ResetTimer = 0;
    float m_ResetLength = 1.5;
};