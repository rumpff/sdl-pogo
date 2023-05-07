#include "PlayerObject.h"

// PlayerObject
void PlayerObject::OnCreate()
{
    Tag = "player";
    HandlePhysics = true;
    Position = { 1280.0f / 2.0f, 720.0f / 2.0f };
    Velocity = { 0.0f, -0.0f };
    ColliderLength = 50.0f;
    Rotation = -M_PI / 2.0f;

    ChangeState(new PlayerAirborneState());
}

void PlayerObject::Tick(double deltaTime)
{
    if (m_CurrentState != 0)
        m_CurrentState->StateTick(deltaTime);
}

void PlayerObject::Render(SDL_Renderer* renderer)
{
    //SDL_FRect fillRect = { Position.x - (ColliderLength /2), Position.y - (ColliderLength / 2), 
    //    ColliderLength, ColliderLength };

    //SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    //SDL_RenderFillRectF(renderer, &fillRect);

    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_FPoint handleBarLocation =
    {
        cosf(Rotation) * (ColliderLength/2 * (1 - m_VisualCharge)) + Position.x,
        sinf(Rotation) * (ColliderLength/2 * (1 - m_VisualCharge)) + Position.y
    };

    float barSize = 15;

    std::pair< SDL_FPoint, SDL_FPoint> handleBar
    {
        {
            (cosf(Rotation + (M_PI / 2.0f)) * barSize) + handleBarLocation.x,
            (sinf(Rotation + (M_PI / 2.0f)) * barSize) + handleBarLocation.y
        },

        {
            (cosf(Rotation - (M_PI / 2.0f)) * barSize) + handleBarLocation.x,
            (sinf(Rotation - (M_PI / 2.0f)) * barSize) + handleBarLocation.y
        }
    };

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, handleBarLocation.x, handleBarLocation.y, collider.second.x, collider.second.y);
    SDL_RenderDrawLineF(renderer, handleBar.first.x, handleBar.first.y, handleBar.second.x, handleBar.second.y);
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

