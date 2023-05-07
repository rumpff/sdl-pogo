#include "FinishObject.h"

void FinishObject::OnCreate()
{
    Type = LevelFinish;
    HandlePhysics = false;
    PhysicsMode = Trigger;
}

void FinishObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}