#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Collision.h"

#include <cmath>
#include <sstream>

class PlayerObject :
    public GameObject
{
public:
    SDL_FPoint kut = { 0,0 };
    const float JumpHeight = 0.2;

    virtual void OnCreate();
    virtual void Tick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    void ChangeState(PlayerState* newState);

    virtual void OnCollisionEnter(Collision c);
    virtual void OnCollision(Collision c);
    virtual void OnCollisionExit(Collision c);

    virtual void OnTriggerEnter(Collision c);
    virtual void OnTrigger(Collision c);
    virtual void OnTriggerExit(Collision c);

private:
    PlayerState* m_CurrentState;

};

