#pragma once
#include "GameObject.h"


class HazardGeometryObject :
    public GameObject
{
public:
    virtual void OnCreate();
    virtual void Render(SDL_Renderer* renderer);
};

