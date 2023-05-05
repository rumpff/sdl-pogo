#include "PlayerState.h"
#include "PlayerObject.h"

void PlayerState::StateEnter(PlayerObject* player)
{
    m_Player = player;
}


// --- Grounded state --- //


void PlayerGroundedState::StateEnter(PlayerObject* player)
{
    PlayerState::StateEnter(player);

    m_Player->HandlePhysics = false;

    m_Anchor = m_Player->GetCollider().second;

    printf("im ground");
}

void PlayerGroundedState::StateTick(double deltaTime)
{
    // Check input (this could be cleaner?)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        Jump();
        return;
    }

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        Rotate(-10 * deltaTime);
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        Rotate(10 * deltaTime);
    }

    // Snap player to anchor
    m_Player->Position = SDL_FPoint
    {
        m_Anchor.x + (cos(m_Player->Rotation) * (m_Player->ColliderLength * 0.5f)),
        m_Anchor.y + (sin(m_Player->Rotation) * (m_Player->ColliderLength * 0.5f))
    };
}

void PlayerGroundedState::StateExit()
{
    //hm
}

void PlayerGroundedState::Rotate(float amount)
{
    m_Player->Rotation += amount;
}

void PlayerGroundedState::Jump()
{
    m_Player->Velocity =
    {
        cosf(m_Player->Rotation) * m_Player->JumpHeight,
        sinf(m_Player->Rotation) * m_Player->JumpHeight
    };
    m_Player->ChangeState(new PlayerAirborneState());
}


// --- Airborne state --- //


void PlayerAirborneState::StateEnter(PlayerObject* player)
{
    PlayerState::StateEnter(player);

    printf("im air");

    m_Player->HandlePhysics = true;
}

void PlayerAirborneState::StateTick(double deltaTime)
{
    //hm
}

void PlayerAirborneState::StateExit()
{
    //hm
}

void PlayerAirborneState::OnCollision(GameObject* o)
{
    printf(o->Tag.c_str());

    if(o->Tag == "geometry")
    {
        // Decide if player bounces or gets grounded
        Ground();
    }
}

void PlayerAirborneState::Ground()
{
    printf("yuuupp");

    m_Player->ChangeState(new PlayerGroundedState());
}

void PlayerAirborneState::Bounce()
{

}