#pragma once

#include <SDL.h>

// They are gaming
class GameObject
{
public:
	virtual void GameTick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);
};

