#include "PlayerObject.h"
#include <sstream>


void PlayerObject::OnCreate()
{
    HandlePhysics = true;
    Position = { 1280 / 2, 720 / 2 };
}

void PlayerObject::Tick(double deltaTime)
{
    // Nog niks
}

void PlayerObject::Render(SDL_Renderer* renderer)
{
    float rectSize = 100 / 2.0;

    SDL_FRect fillRect = { Position.x, Position.y, rectSize, rectSize };

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRectF(renderer, &fillRect);
}