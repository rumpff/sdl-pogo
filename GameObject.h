#pragma once

#include <sstream>
#include <cmath>
#include <vector>
#include <utility>
#include <SDL.h>

#include "Collision.h"
#include "LevelData.h"

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
	ObjectType Type = Undefined;
	bool HandlePhysics = false;
	CollisionMode PhysicsMode = Passthrough;
	std::vector<GameObject*> CollidingObjects;

	SDL_FPoint Position, PositionPrev;
	float Rotation, RotationPrev;
	SDL_FPoint Velocity;
	float AngularVelocity;
	
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void Tick(double deltaTime);
	virtual void UpdatePrev();
	virtual void Render(SDL_Renderer* renderer);

	virtual void SetColliderLength(float newLength) { m_ColliderLength = newLength; }
	float GetColliderLength() { return m_ColliderLength; }

	virtual void OnCollisionEnter(Collision c);
	virtual void OnCollision(Collision c);
	virtual void OnCollisionExit(Collision c);

	virtual void OnTriggerEnter(Collision c);
	virtual void OnTrigger(Collision c);
	virtual void OnTriggerExit(Collision c);

	/// <summary>
	/// Calculates collider line segment in local space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderLocal();
	/// <summary>
	/// Calculates collider line segment in world space
	/// </summary>
	std::pair < SDL_FPoint, SDL_FPoint> GetCollider();

	/// Use RotationPrev to calculate collider line segment in local space
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderPrevLocal();
	/// <summary>
	/// Use RotationPrev to calculate collider line segment in world space 
	/// </summary>
	/// <returns></returns>
	std::pair < SDL_FPoint, SDL_FPoint> GetColliderPrev();

protected:
	float m_ColliderLength;

	std::pair< SDL_FPoint, SDL_FPoint> CalcLine(float angle, float length);
};

