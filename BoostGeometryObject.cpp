#include "BoostGeometryObject.h"

void BoostGeometryObject::OnCreate()
{
    Type = GeometryBoost;
    HandlePhysics = false;
    PhysicsMode = Trigger;
}

void BoostGeometryObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    
    SDL_SetRenderDrawColor(renderer, 0x98, 0xD8, 0xAA, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}