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

	virtual void OnCollisionEnter(GameObject* o);
	virtual void OnCollision(GameObject* o);
	virtual void OnCollisionExit(GameObject* o);

	virtual void OnTriggerEnter(GameObject* o);
	virtual void OnTrigger(GameObject* o);
	virtual void OnTriggerExit(GameObject* o);

	/// <summary>
	/// Calculates collider line segment in local space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderLocal();
	/// <summary>
	/// Calculates collider line segment in world space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetCollider();
};

