#pragma once
#include "GameObject.h"
#include "PlayerStates.h"
#include "Collision.h"

#include <cmath>
#include <sstream>

class PlayerObject :
    public GameObject
{
public:
    const float JumpHeight = 800;

    float JumpCharge = 0;

    bool Finished = false;
    bool Dead = false;

    virtual void OnCreate();
    virtual void Tick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    virtual void SetColliderLength(float newLength) { /* prefent collider changes */ }

    void ChangeState(PlayerState* newState);
    void SetVisualCharge(float charge) { m_VisualCharge = charge; }

    virtual void OnCollisionEnter(Collision c);
    virtual void OnCollision(Collision c);
    virtual void OnCollisionExit(Collision c);

    virtual void OnTriggerEnter(Collision c);
    virtual void OnTrigger(Collision c);
    virtual void OnTriggerExit(Collision c);

private:
    PlayerState* m_CurrentState;
    float m_VisualCharge = 0;
};

