#include "PlayerStates.h"
#include "PlayerObject.h"

void PlayerState::StateEnter(PlayerObject* player)
{
    m_Player = player;
}

void PlayerState::Bounce(Collision c)
{
    m_Player->Velocity = VectorBounce(c.ImpactVelocity, CollisionNormal(c), 0.6f);

    // Bounce rotate
    float normalAngle = atan2(CollisionNormal(c).y, CollisionNormal(c).x);

    // Rotate normal when landing on head
    normalAngle -= (c.ColliderAnchor == 1) ? M_PI : 0;

    float angleVelocity = AngleDifference(m_Player->Rotation, normalAngle);

    angleVelocity *= BounceRotate;

    m_Player->AngularVelocity = angleVelocity;
}

SDL_FPoint PlayerState::CollisionNormal(Collision c)
{
    std::pair<SDL_FPoint, SDL_FPoint> colliderNormals{
    { cosf(c.Object->Rotation - (M_PI * 0.5)), sinf(c.Object->Rotation - (M_PI * 0.5)) },
    { cosf(c.Object->Rotation + (M_PI * 0.5)), sinf(c.Object->Rotation + (M_PI * 0.5)) },
    };
    SDL_FPoint impactReversed{
        c.ImpactVelocity.x * -1,
        c.ImpactVelocity.y * -1
    };

    // check which normal points most towards impact vector
    float distToFirst = std::hypotf(impactReversed.x - colliderNormals.first.x, impactReversed.y - colliderNormals.first.y);
    float distToSecond = std::hypotf(impactReversed.x - colliderNormals.second.x, impactReversed.y - colliderNormals.second.y);

    return (distToFirst <= distToSecond) ? colliderNormals.first : colliderNormals.second;
}

SDL_FPoint PlayerState::VectorBounce(SDL_FPoint velocity, SDL_FPoint normal, float friction)
{
    // https://stackoverflow.com/a/573206
    SDL_FPoint u = VectorMultiply(normal, Dot(velocity, normal) / Dot(normal, normal));
    SDL_FPoint w = VectorSubtract(velocity, u);

    return VectorSubtract(VectorMultiply(w, friction), VectorMultiply(u, 1));
}

float PlayerState::Dot(SDL_FPoint a, SDL_FPoint b)
{
    return a.x * b.x + a.y * b.y;
}
float PlayerState::Mod(float a, float n)
{
    return a - floor(a / n) * n;
}
float PlayerState::AngleDifference(float target, float source)
{
    // https://stackoverflow.com/a/7869457

    float angle = target - source;
    angle = Mod((angle + M_PI), M_PI * 2) - M_PI;
    return angle;
}
SDL_FPoint PlayerState::VectorMultiply(SDL_FPoint a, float b)
{
    return SDL_FPoint
    {
        a.x * b,
        a.y * b
    };
}
SDL_FPoint PlayerState::VectorDivide(SDL_FPoint a, SDL_FPoint b)
{
    return SDL_FPoint
    {
        a.x / b.x,
        a.y / b.y
    };
}
SDL_FPoint PlayerState::VectorSubtract(SDL_FPoint a, SDL_FPoint b)
{
    return SDL_FPoint
    {
        a.x - b.x,
        a.y - b.y
    };
}


// --- Grounded state --- //

PlayerGroundedState::PlayerGroundedState(SDL_FPoint groundNormal)
{
    m_GroundNormal = groundNormal;
}

void PlayerGroundedState::StateEnter(PlayerObject* player)
{
    PlayerState::StateEnter(player);

    m_Player->HandlePhysics = false;

    m_Anchor = m_Player->GetCollider().second;
}

void PlayerGroundedState::StateTick(double deltaTime)
{
    // Check input (this could be cleaner?)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LSHIFT])
    {
        Charge(deltaTime / FullChargeDuration);
    }
    else
    {
        if (m_Charge < ChargeThreshold)
        {
            // decharge jump
            Charge(-deltaTime / DeChargeDuration);
        }
        else 
        {
            Jump();
            return;
        }
    }

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        Rotate(-SwivelSpeed * deltaTime);
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        Rotate(SwivelSpeed * deltaTime);
    }

    // Snap player to anchor
    m_Player->Position = SDL_FPoint
    {
        m_Anchor.x + (cos(m_Player->Rotation) * (m_Player->GetColliderLength() * 0.5f)),
        m_Anchor.y + (sin(m_Player->Rotation) * (m_Player->GetColliderLength() * 0.5f))
    };
}

void PlayerGroundedState::StateExit()
{
    m_Player->SetCharge(0);
}

bool PlayerGroundedState::Rotate(float amount)
{
    // Check if rotation is allowed
    float newAngle = m_Player->Rotation + amount;
    float normalAngle = atan2(m_GroundNormal.y, m_GroundNormal.x);

    float newDifference = fabsf(AngleDifference(newAngle, normalAngle));

    if (newDifference >= MaxSwivelAngle)
    {
        // allow pogo to move back, but not further
        float currentDifference = fabsf(AngleDifference(m_Player->Rotation, normalAngle));

        if (newDifference >= currentDifference)
            return false;
    }

    m_Player->Rotation = newAngle;
    return true;
}

void PlayerGroundedState::Charge(float amount)
{
    m_Charge = SDL_clamp(m_Charge + amount, 0, 1);

    m_Player->SetCharge(m_Charge);
    m_Player->ShowTrajectory(JumpVelocity());
}

void PlayerGroundedState::Jump()
{
    m_Player->Velocity = JumpVelocity();
    m_Player->ChangeState(new PlayerAirborneState());
}

SDL_FPoint PlayerGroundedState::JumpVelocity()
{
    float jumpHeight = m_Player->JumpHeight * m_Charge;

    return
    {
        cosf(m_Player->Rotation) * jumpHeight,
        sinf(m_Player->Rotation) * jumpHeight
    };
}



// --- Airborne state --- //


void PlayerAirborneState::StateEnter(PlayerObject* player)
{
    PlayerState::StateEnter(player);

    m_Player->HandlePhysics = true;
    m_Player->AngularVelocity = 0;
}

void PlayerAirborneState::StateTick(double deltaTime)
{
    // Check input (this could be cleaner?)
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        m_Player->AngularVelocity -= 50 * deltaTime;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        m_Player->AngularVelocity += 50 * deltaTime;
    }
}

void PlayerAirborneState::StateExit()
{
    //hm
}

void PlayerAirborneState::OnCollision(Collision c)
{
    switch(c.Object->Type)
    {      
    case GeometryNormal:
        if (c.ColliderAnchor == 1)
        {
            // Collision with top of pogo
            Bounce(c);
        }
        if (c.ColliderAnchor == 2)
        {
            // Collision with bottom of pogo
            Ground(c);
        }
        break;

    case GeometryHazard:
        Bounce(c);
        m_Player->Dead = true;
        break;
    }
}

void PlayerAirborneState::OnTriggerEnter(Collision c)
{
    switch (c.Object->Type)
    {
    case LevelFinish:
        m_Player->Finished = true;
        break;
    }
}

void PlayerAirborneState::Ground(Collision c)
{
    m_Player->ChangeState(new PlayerGroundedState(CollisionNormal(c)));
}


// --- Limp State --- //

void PlayerLimpState::StateEnter(PlayerObject* player)
{
    PlayerState::StateEnter(player);

    m_Player->HandlePhysics = true;
}

void PlayerLimpState::OnCollision(Collision c)
{
    switch (c.Object->Type)
    {
    case GeometryNormal: case GeometryHazard:
        Bounce(c);
        break;
    }
}