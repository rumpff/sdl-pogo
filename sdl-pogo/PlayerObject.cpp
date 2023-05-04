#include "PlayerObject.h"
#include <cmath>

void PlayerObject::OnCreate()
{
    HandlePhysics = true;
    Position = { 1280.0f / 2.0f, 720.0f / 2.0f };
    Velocity = { 0.0f, -4.0f };
    ColliderLength = 50.0f;
    Rotation = -M_PI / 2;
}

void PlayerObject::Tick(double deltaTime)
{
    // Nog niks
}

void PlayerObject::Render(SDL_Renderer* renderer)
{
    SDL_FRect fillRect = { Position.x - (ColliderLength /2), Position.y - (ColliderLength / 2), 
        ColliderLength, ColliderLength };

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRectF(renderer, &fillRect);


    // Draw collider
    std::pair < SDL_FPoint, SDL_FPoint> collider = GetCollider();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(renderer, + collider.first.x, + collider.first.y, collider.second.x, collider.second.y);


    SDL_FRect marker = { collider.first.x, collider.first.y, 10, 10 };
    SDL_RenderFillRectF(renderer, &marker);
}