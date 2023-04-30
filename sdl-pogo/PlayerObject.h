#pragma once
#include "GameObject.h"
class PlayerObject :
    public GameObject
{
public:
    virtual void OnCreate();
    virtual void Tick(double deltaTime);
    virtual void Render(SDL_Renderer* renderer);
};

