#pragma once
#include "GameObject.h"
#include "PlayerStates.h"
#include "Collision.h"

#include <cmath>
#include <sstream>https://discord.com/channels/@me/941736042308980747

class PlayerObject :
    public GameObject
{
public:
    const float JumpHeight = 800;

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

