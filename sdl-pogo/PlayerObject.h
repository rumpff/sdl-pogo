#pragma once
#include "GameObject.h"
class PlayerObject :
    public GameObject
{
public:
    virtual void GameTick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);
};

