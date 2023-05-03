#pragma once
#include "GameObject.h"


class GeometryObject :
    public GameObject
{
    virtual void OnCreate();
    virtual void Render(SDL_Renderer* renderer);
};

