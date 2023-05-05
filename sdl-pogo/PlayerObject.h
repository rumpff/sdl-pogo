#pragma once
#include "GameObject.h"
#include "PlayerState.h"

#include <cmath>
#include <sstream>

class PlayerObject :
    public GameObject
{
public:
    const float JumpHeight = 0.1;

    virtual void OnCreate();
    virtual void Tick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    void ChangeState(PlayerState* newState);

    virtual void OnCollisionEnter(GameObject* o);
    virtual void OnCollision(GameObject* o);
    virtual void OnCollisionExit(GameObject* o);

    virtual void OnTriggerEnter(GameObject* o);
    virtual void OnTrigger(GameObject* o);
    virtual void OnTriggerExit(GameObject* o);

private:
    PlayerState* m_CurrentState;

};

