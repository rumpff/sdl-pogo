#include "PlayerObject.h"

void PlayerObject::GameTick(double deltaTime)
{
    // Nog niks
}

void PlayerObject::Render(SDL_Renderer* renderer)
{
    SDL_Rect fillRect = { 1280 / 4, 720 / 4, 1280 / 2, 720 / 2 };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &fillRect);
}