#pragma once

#include "GameObject.h"

#include <cmath>

class PlayerObject;
class PlayerState
{
public:
    virtual void StateEnter(PlayerObject* player);
    virtual void StateTick(double deltaTime) { };
    virtual void StateExit() { };

    virtual void OnCollisionEnter(Collision c) { };
    virtual void OnCollision(Collision c) { };
    virtual void OnCollisionExit(Collision c) { };

    virtual void OnTriggerEnter(Collision c) { };
    virtual void OnTrigger(Collision c) { };
    virtual void OnTriggerExit(Collision c) { };

    protected:
        PlayerObject* m_Player = 0;
};

class PlayerGroundedState : public PlayerState
{
public:
    virtual void StateEnter(PlayerObject* player);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();

private:
    SDL_FPoint m_Anchor = {0, 0};

    void Rotate(float amount);
    void Jump();
};

class PlayerAirborneState : public PlayerState
{
public:
    virtual void StateEnter(PlayerObject* player);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();

    virtual void OnCollision(Collision c);

private:
    void Ground();
    void Bounce(Collision c);
    float VectorAngle(SDL_FPoint a, SDL_FPoint b);
};