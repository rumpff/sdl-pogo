#pragma once

#include <cmath>
#include <utility>
#include <SDL.h>

// They are gaming
class GameObject
{
public:
	bool HandlePhysics = false;
	SDL_FPoint Position, PositionPrev;
	float Rotation;
	float ColliderLength;

	SDL_FPoint Velocity;
	float AngularVelocity;
	
	virtual void OnCreate();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	virtual void OnCollision();

	/// <summary>
	/// Calculates collider line segment in local space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderLocal();
	/// <summary>
	/// Calculates collider line segment in world space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetCollider();
};

