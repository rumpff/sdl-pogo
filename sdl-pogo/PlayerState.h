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

    virtual void OnCollisionEnter(GameObject* o) { };
    virtual void OnCollision(GameObject* o) { };
    virtual void OnCollisionExit(GameObject* o) { };

    virtual void OnTriggerEnter(GameObject* o) { };
    virtual void OnTrigger(GameObject* o) { };
    virtual void OnTriggerExit(GameObject* o) { };

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

    virtual void OnCollision(GameObject* o);

private:
    void Ground();
    void Bounce();
};