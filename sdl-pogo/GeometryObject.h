#pragma once
#include "GameObject.h"


class GeometryObject :
    public GameObject
{
public:
    virtual void OnCreate();
    virtual void Render(SDL_Renderer* renderer);
};

