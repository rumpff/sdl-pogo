#include "PlayerObject.h"

// PlayerObject
void PlayerObject::OnCreate()
{
    Type = Player;
    HandlePhysics = true;
    Velocity = { 0.0f, -0.0f };
    m_ColliderLength = 50.0f;

    ChangeState(new PlayerAirborneState());
}

void PlayerObject::Tick(double deltaTime)
{
    if (m_CurrentState != 0)
        m_CurrentState->StateTick(deltaTime);
}

void PlayerObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    float chargeScale = 0.5;
    float charge = m_VisualCharge * chargeScale;

    SDL_FPoint headLocation =
    {
        cosf(Rotation) * (m_ColliderLength/2 * (1 - charge)) + Position.x,
        sinf(Rotation) * (m_ColliderLength/2 * (1 - charge)) + Position.y
    };

    float handleOffset = 5;
    SDL_FPoint handleLocation =
    {
        cosf(Rotation) * (m_ColliderLength / 2 * (1 - charge) - handleOffset) + Position.x,
        sinf(Rotation) * (m_ColliderLength / 2 * (1 - charge) - handleOffset) + Position.y
    };

    float footOffset = 25;
    SDL_FPoint footpedalLocation =
    {
        cosf(Rotation) * (m_ColliderLength / 2 * (1 - charge) - footOffset) + Position.x,
        sinf(Rotation) * (m_ColliderLength / 2 * (1 - charge) - footOffset) + Position.y
    };

    float handleSize = 8;

    std::pair< SDL_FPoint, SDL_FPoint> handleBar
    {
        {
            (cosf(Rotation + (M_PI / 2.0f)) * handleSize) + handleLocation.x,
            (sinf(Rotation + (M_PI / 2.0f)) * handleSize) + handleLocation.y
        },

        {
            (cosf(Rotation - (M_PI / 2.0f)) * handleSize) + handleLocation.x,
            (sinf(Rotation - (M_PI / 2.0f)) * handleSize) + handleLocation.y
        }
    };

    float footSize = handleSize;

    std::pair< SDL_FPoint, SDL_FPoint> footBar
    {
        {
            (cosf(Rotation + (M_PI / 2.0f)) * footSize) + footpedalLocation.x,
            (sinf(Rotation + (M_PI / 2.0f)) * footSize) + footpedalLocation.y
        },

        {
            (cosf(Rotation - (M_PI / 2.0f)) * footSize) + footpedalLocation.x,
            (sinf(Rotation - (M_PI / 2.0f)) * footSize) + footpedalLocation.y
        }
    };

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, headLocation.x, headLocation.y, collider.second.x, collider.second.y);
    SDL_RenderDrawLineF(renderer, handleBar.first.x, handleBar.first.y, handleBar.second.x, handleBar.second.y);
    SDL_RenderDrawLineF(renderer, footBar.first.x, footBar.first.y, footBar.second.x, footBar.second.y);
}

void PlayerObject::OnCollisionEnter(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnCollisionEnter(c);
}
void PlayerObject::OnCollision(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnCollision(c);
}
void PlayerObject::OnCollisionExit(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnCollisionExit(c);
}

void PlayerObject::OnTriggerEnter(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnTriggerEnter(c);
}
void PlayerObject::OnTrigger(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnTrigger(c);
}
void PlayerObject::OnTriggerExit(Collision c)
{
    if (m_CurrentState != 0)
        m_CurrentState->OnTriggerExit(c);
}

void PlayerObject::ChangeState(PlayerState* newState)
{
    if (m_CurrentState != 0)
    {
        m_CurrentState->StateExit();
        delete m_CurrentState;
    }
        
    m_CurrentState = newState;
    m_CurrentState->StateEnter(this);
}

