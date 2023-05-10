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

    const float BounceRotate = 12;
    void Bounce(Collision c);
    SDL_FPoint VectorBounce(SDL_FPoint velocity, SDL_FPoint normal, float friction);
    SDL_FPoint CollisionNormal(Collision c);

protected:
    PlayerObject* m_Player = 0;

    float Dot(SDL_FPoint a, SDL_FPoint b);
    float Mod(float a, float n);

    float AngleDifference(float target, float source);

    SDL_FPoint VectorMultiply(SDL_FPoint a, float b);
    SDL_FPoint VectorDivide(SDL_FPoint a, SDL_FPoint b);
    SDL_FPoint VectorSubtract(SDL_FPoint a, SDL_FPoint b);
};

class PlayerGroundedState : public PlayerState
{
public:
    PlayerGroundedState(SDL_FPoint groundNormal);
    virtual void StateEnter(PlayerObject* player);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();

private:
    const float MaxSwivelAngle = M_PI / 6;
    const float SwivelSpeed = 3;
    const float FullChargeDuration = 0.35f;
    const float DeChargeDuration = 0.75;
    const float ChargeThreshold = 0.2;

    float m_Charge = 0;
    SDL_FPoint m_GroundNormal{ 0, 1 };
    SDL_FPoint m_Anchor = { 0, 0 };

    void Charge(float amount);
    void Jump();

    bool Rotate(float amount);
};

class PlayerAirborneState : public PlayerState
{
public:
    virtual void StateEnter(PlayerObject* player);
    virtual void StateTick(double deltaTime);
    virtual void StateExit();

    virtual void OnCollision(Collision c);
    virtual void OnTriggerEnter(Collision c);

private:
    void Ground(Collision c);
};

class PlayerLimpState : public PlayerState
{
public:
    virtual void StateEnter(PlayerObject* player);

    virtual void OnCollision(Collision c);
};