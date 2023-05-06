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
    std::pair<SDL_FPoint, SDL_FPoint> colliderNormals {   
        { cosf(c.Object->Rotation - (M_PI * 0.5)), sinf(c.Object->Rotation - (M_PI * 0.5)) },
        { cosf(c.Object->Rotation + (M_PI * 0.5)), sinf(c.Object->Rotation + (M_PI * 0.5)) },
    };
    SDL_FPoint impactReversed {
        c.ImpactVelocity.x * -1,
        c.ImpactVelocity.y * -1
    };

    // check which normal points most towards impact vector
    float distToFirst = std::hypotf(impactReversed.x - colliderNormals.first.x, impactReversed.y - colliderNormals.first.y);
    float distToSecond = std::hypotf(impactReversed.x - colliderNormals.second.x, impactReversed.y - colliderNormals.second.y);

    SDL_FPoint normal = (distToFirst <= distToSecond) ? colliderNormals.first : colliderNormals.second;

    m_Player->kut = normal;

    printf("\nrotate: ");
    printf(std::to_string(c.Object->Rotation).c_str());

    m_Player->Velocity = VectorBounce(c.ImpactVelocity, normal, 0.6f);
}

float PlayerAirborneState::Dot(SDL_FPoint a, SDL_FPoint b)
{
    return a.x * b.x + a.y * b.y;
}

float PlayerAirborneState::VectorAngle(SDL_FPoint a, SDL_FPoint b)
{
    // https://stackoverflow.com/a/16544330
    float det = a.x * b.y - a.y * b.x; // determinant
    float angle = atan2(det, Dot(a,b)); // atan2(y, x) or atan2(sin, cos)
    
    return angle;
}

SDL_FPoint PlayerAirborneState::VectorBounce(SDL_FPoint velocity, SDL_FPoint normal, float friction)
{
    // https://stackoverflow.com/a/573206
    SDL_FPoint u = VectorMultiply(normal, Dot(velocity, normal) / Dot(normal, normal));
    SDL_FPoint w = VectorSubtract(velocity, u);

    return VectorSubtract(VectorMultiply(w, friction), VectorMultiply(u, 1));
}

SDL_FPoint PlayerAirborneState::VectorMultiply(SDL_FPoint a, float b)
{
    return SDL_FPoint
    {
        a.x * b,
        a.y * b
    };
}
SDL_FPoint PlayerAirborneState::VectorDivide(SDL_FPoint a, SDL_FPoint b)
{
    return SDL_FPoint
    {
        a.x / b.x,
        a.y / b.y
    };
}
SDL_FPoint PlayerAirborneState::VectorSubtract(SDL_FPoint a, SDL_FPoint b)
{
    return SDL_FPoint
    {
        a.x - b.x,
        a.y - b.y
    };
}