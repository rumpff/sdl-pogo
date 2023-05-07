#include "HazardGeometryObject.h"

void HazardGeometryObject::OnCreate()
{
    Type = GeometryHazard;
    HandlePhysics = false;
    PhysicsMode = Rigid;
}

void HazardGeometryObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}