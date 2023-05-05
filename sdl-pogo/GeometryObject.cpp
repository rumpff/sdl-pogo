#include "GeometryObject.h"



void GeometryObject::OnCreate()
{
    Tag = "geometry";
    HandlePhysics = false;
    PhysicsMode = Rigid;
    Position = { 1280 / 2, 720 / 1.5f };
    ColliderLength = 720;  
    Rotation = 0;
}

void GeometryObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}