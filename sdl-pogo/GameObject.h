#pragma once

#include <utility>
#include <SDL.h>

// They are gaming
class GameObject
{
public:
	bool HandlePhysics = false;
	SDL_FPoint Position;
	float Rotation;

	SDL_FPoint Velocity;
	float AngularVelocity;
	
	virtual void OnCreate();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);
};

