#pragma once
#include "GameObject.h"
#include "PlayerStates.h"
#include "Collision.h"
#include "SimpleEasing.h"

#include <cmath>
#include <vector>
#include <sstream>

class PlayerObject :
    public GameObject
{
public:
    const SDL_FPoint Gravity{ 0, 1500.0f };
    const float JumpHeight = 800;

    float JumpCharge = 0;

    bool Finished = false;
    bool Dead = false;


    virtual void OnCreate();
    virtual void Tick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    virtual void SetColliderLength(float newLength) { /* prefent collider changes */ }

    void ChangeState(PlayerState* newState);
    void SetCharge(float charge) { m_Charge = charge; }
    void ShowTrajectory(SDL_FPoint velocity);

    virtual void OnCollisionEnter(Collision c);
    virtual void OnCollision(Collision c);
    virtual void OnCollisionExit(Collision c);

    virtual void OnTriggerEnter(Collision c);
    virtual void OnTrigger(Collision c);
    virtual void OnTriggerExit(Collision c);

private:
    PlayerState* m_CurrentState;
    float m_Charge = 0;
    std::vector<SDL_FPoint> m_Trajectory;
    const float TrajectoryPoints = 100;
    const float TrajectoryStepSize = 0.02;
};

