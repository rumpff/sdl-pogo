#pragma once
#include "Manager.h"

class UI :
    public Manager
{
public:
    virtual void Close() { }
    virtual void Tick(double deltaTime) { }
    virtual void Render(SDL_Renderer* renderer) { }
};

