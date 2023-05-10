#include "GeometryObject.h"

void GeometryObject::OnCreate()
{
    Type = GeometryNormal;
    HandlePhysics = false;
    PhysicsMode = Rigid;
}

void GeometryObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}