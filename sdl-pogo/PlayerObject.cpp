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
    float charge = m_Charge * chargeScale;

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

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawLineF(renderer, headLocation.x, headLocation.y, collider.second.x, collider.second.y);
    SDL_RenderDrawLineF(renderer, handleBar.first.x, handleBar.first.y, handleBar.second.x, handleBar.second.y);
    SDL_RenderDrawLineF(renderer, footBar.first.x, footBar.first.y, footBar.second.x, footBar.second.y);

    // draw jump trajectory
    if (m_Charge != 0)
    {
        printf("gonna draw the ting\n");
        
        for (size_t i = 1; i < m_Trajectory.size(); i++)
        {
            printf("drawing the ting\n");
            
            float alpha = Easing::EaseOutSine(i, 255, -255, m_Trajectory.size());
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, alpha);
            SDL_RenderDrawLineF(renderer, m_Trajectory[i-1].x, m_Trajectory[i-1].y, m_Trajectory[i].x, m_Trajectory[i].y);
        }
    }
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

void PlayerObject::ShowTrajectory(SDL_FPoint velocity)
{
    m_Trajectory.clear();

    SDL_FPoint tPos = Position;

    for (size_t i = 0; i < TrajectoryPoints; i++)
    {
        printf("calculating the ting\n");
        // use the same code as in object manager
        velocity.x += Gravity.x * TrajectoryStepSize;
        velocity.y += Gravity.y * TrajectoryStepSize;

        tPos.x += velocity.x * TrajectoryStepSize;
        tPos.y += velocity.y * TrajectoryStepSize;

        m_Trajectory.push_back(tPos);
    }
}