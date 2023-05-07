#pragma once

#include <SDL.h>

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
    //virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    //virtual void StateExit();
};

class GameState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();
};

class EndGameState : public GameLevelState
{
public:
    virtual void StateEnter(GameLevelManager* m);
    virtual void StateTick(double deltaTime);
    //virtual void StateExit();
};