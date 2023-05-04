#pragma once

#include <sstream>
#include <cmath>
#include <vector>
#include <utility>
#include <SDL.h>

enum CollisionMode
{
	Rigid,
	Trigger,
	Passthrough
};

// They are gaming
class GameObject
{
public:
	bool HandlePhysics = false;
	CollisionMode PhysicsMode = Passthrough;
	std::vector<GameObject*> CollidingObjects;

	SDL_FPoint Position, PositionPrev;
	float Rotation;
	float ColliderLength;

	SDL_FPoint Velocity;
	float AngularVelocity;
	
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void Tick(double deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	virtual void OnCollisionEnter();
	virtual void OnCollision();
	virtual void OnCollisionExit();

	virtual void OnTriggerEnter();
	virtual void OnTrigger();
	virtual void OnTriggerExit();

	/// <summary>
	/// Calculates collider line segment in local space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderLocal();
	/// <summary>
	/// Calculates collider line segment in world space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetCollider();
};

