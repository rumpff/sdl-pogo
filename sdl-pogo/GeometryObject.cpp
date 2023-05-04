#include "GeometryObject.h"



void GeometryObject::OnCreate()
{
    HandlePhysics = false;
    Position = { 1280 / 2, 720 / 1.5f };
    ColliderLength = 300;  
    Rotation = 10;
}

void GeometryObject::Render(SDL_Renderer* renderer)
{
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, collider.first.x, collider.first.y, collider.second.x, collider.second.y);
}