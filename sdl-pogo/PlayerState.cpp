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

    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        m_Player->Rotation = -M_PI / 2;
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
    // Check input (this could be cleaner?)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        m_Player->Rotation -= 10 * deltaTime;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        m_Player->Rotation += 10 * deltaTime;
    }
}

void PlayerAirborneState::StateExit()
{
    //hm
}

void PlayerAirborneState::OnCollision(Collision c)
{
    if(c.Object->Tag == "geometry")
    {
        if (c.ColliderAnchor == 1)
        {
            Bounce(c);
        }
        if (c.ColliderAnchor == 2)
        {
            Ground();
        }
    }
}

void PlayerAirborneState::Ground()
{
    m_Player->ChangeState(new PlayerGroundedState());
}

void PlayerAirborneState::Bounce(Collision c)
{    
    SDL_FPoint normal;

    // Find collider normal
    SDL_FPoint normalCounterClock { cos(c.Object->Rotation - (M_PI / 2)), sin(c.Object->Rotation - (M_PI / 2)) };
    SDL_FPoint normalClock { cos(c.Object->Rotation + (M_PI / 2)), sin(c.Object->Rotation + (M_PI / 2)) };
    SDL_FPoint impactReverse { -c.ImpactVelocity.x, -c.ImpactVelocity.y };

    float angleDiffCC = VectorAngle(normalCounterClock, impactReverse);
    float angleDiffC = VectorAngle(normalClock, impactReverse);

    if (angleDiffC <= angleDiffCC) { normal = normalClock; }
    else { normal = normalCounterClock; }

    // Calculate reflect vector
    float reflectAngle = c.Object->Rotation - VectorAngle(impactReverse, normal);
    float bounceForce = std::hypot(c.ImpactVelocity.x, c.ImpactVelocity.y);

    m_Player->Velocity =
    {
        cos(reflectAngle) * bounceForce,
        sin(reflectAngle) * bounceForce
    };

    printf("bounce - ");
    printf("reflect angle: "); printf(std::to_string(reflectAngle).c_str()); printf("\n");
}

float PlayerAirborneState::VectorAngle(SDL_FPoint a, SDL_FPoint b)
{
    // https://stackoverflow.com/a/16544330
    float dot = a.x * b.x + a.y * b.y; // dot product
    float det = a.x * b.y - a.y * b.x; // determinant
    float angle = atan2(det, dot); // atan2(y, x) or atan2(sin, cos)
    
    return angle;
}