#pragma once
#include "GameObject.h"
class BoostGeometryObject :
    public GameObject
{
    virtual void OnCreate();
    virtual void Render(SDL_Renderer* renderer);
};

