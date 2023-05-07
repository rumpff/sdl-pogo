#include "ObjectManager.h"

void ObjectManager::Initialize()
{
	CreateObject(new PlayerObject());

	float wallSize = 300;
	for (int i = 0; i < 4; i++)
	{
		GameObject* wall = CreateObject(new GeometryObject());
		wall->ColliderLength = wallSize;

		wall->Rotation = i * ((M_PI * 2) / 4) + (M_PI / 8);
		wall->Position =
		{
			(1280 / 2) - cosf(wall->Rotation - (M_PI/2)) * (wallSize / 2),
			(720 / 2) - sinf(wall->Rotation - (M_PI/2)) * (wallSize / 2)
		};
	}
	
}

void ObjectManager::Close()
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->OnDestroy();
		delete m_GameObjects[i];
	}
}

GameObject* ObjectManager::CreateObject(GameObject* newObject)
{
	m_GameObjects.push_back(newObject);
	newObject->OnCreate();

	return newObject;
}

void ObjectManager::GameTick(double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->UpdatePrev();
		m_GameObjects[i]->Tick(deltaTime);
	}
}

void ObjectManager::PhysicsTick(SDL_FPoint gravity, double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* object = m_GameObjects[i];

		if (!object->HandlePhysics)
			continue;

		SDL_FPoint velocity = object->Velocity;
		float angleVelocity = object->AngularVelocity;

		// Modify Velocities
		velocity.x += gravity.x * deltaTime;
		velocity.y += gravity.y * deltaTime;
		
		angleVelocity = Lerp(angleVelocity, 0, 3 * deltaTime);

		// Apply Velocities
		object->Velocity = velocity;
		object->AngularVelocity = angleVelocity;

		// Move Object
		object->Position.x += object->Velocity.x * deltaTime;
		object->Position.y += object->Velocity.y * deltaTime;

		object->Rotation += object->AngularVelocity * deltaTime;

		std::vector<GameObject*> collideTest = object->CollidingObjects;
		object->CollidingObjects.clear();

		// Check for intersection
		for (size_t j = 0; j < m_GameObjects.size(); j++)
		{
			// Skip self
			if (i == j)
				continue;

			GameObject* otherObject = m_GameObjects[j];

			// Skip if collider is disabled
			if (otherObject->PhysicsMode == Passthrough)
				continue;

			std::pair < SDL_FPoint, SDL_FPoint> objectCollider = object->GetCollider();
			std::pair < SDL_FPoint, SDL_FPoint> otherCollider = otherObject->GetCollider();

			std::pair<bool, SDL_FPoint> intersect = IntersectCheck(objectCollider, otherCollider);

			// Check if intersect
			if (!intersect.first)	
			{
				// Fallback check
				std::pair < SDL_FPoint, SDL_FPoint> path = { object->PositionPrev, object->Position };
				intersect = IntersectCheck(path, otherCollider);

				if (!intersect.first)
					continue;
			}

			// See if object was already colliding
			bool isFirst = true;

			for (size_t k = 0; k < collideTest.size(); k++)
			{
				if (collideTest[k] == otherObject)
				{
					isFirst = false;
					collideTest.erase(collideTest.begin() + k);
					break;
				}
			}


			// Collision has occured
			Collision collision;
			collision.Object = otherObject;
			collision.ImpactVelocity = object->Velocity;

			object->CollidingObjects.push_back(otherObject);

			// Find line end to snap object to
			if (otherObject->PhysicsMode == Rigid)
			{
				SDL_FPoint anchor;
				std::pair < SDL_FPoint, SDL_FPoint> objectColliderLocal = object->GetColliderLocal();
				
				// Use projected point on the other object to see which end is closer
				std::pair< SDL_FPoint, SDL_FPoint> colliderPrev = object->GetColliderPrev();
				std::pair<bool, SDL_FPoint> intersectPrev = IntersectCheck(colliderPrev, otherObject->GetCollider());

				if (intersectPrev.first)
				{
					// printf("huh, a collision?");
				}

				float distToFirst = std::hypotf(colliderPrev.first.x - intersectPrev.second.x, colliderPrev.first.y - intersectPrev.second.y);
				float distToSecond = std::hypotf(colliderPrev.second.x - intersectPrev.second.x, colliderPrev.second.y - intersectPrev.second.y);

				if (distToSecond < distToFirst)
				{
					anchor = objectColliderLocal.second;
					collision.ColliderAnchor = 2;
				}
				else
				{
					anchor = objectColliderLocal.first;
					collision.ColliderAnchor = 1;
				}


				SDL_FPoint newPos
				{
					intersect.second.x - anchor.x,
					intersect.second.y - anchor.y,
				};

				object->Position = newPos;
				object->Velocity = { 0, 0 };

				if (isFirst)
					object->OnCollisionEnter(collision);

				object->OnCollision(collision);
			}
			else if (otherObject->PhysicsMode == Trigger)
			{
				if (isFirst)
					object->OnTriggerEnter(collision);

				object->OnTrigger(collision);
			}
			else
			{
				printf("ERROR! Unimplemented physics mode \n");
			}
		}

		if (collideTest.size() > 0)
		{
			for (size_t k = 0; k < collideTest.size(); k++)
			{
				GameObject* otherObject = collideTest[k];

				Collision collision;
				collision.Object = otherObject;

				if (otherObject->PhysicsMode == Rigid)
				{
					object->OnCollisionExit(collision);
				}
				else if (otherObject->PhysicsMode == Trigger)
				{
					object->OnTriggerExit(collision);
				}
				else
				{
					printf("ERROR! Unimplemented physics mode \n");
				}
			}
		}
	}
}

void ObjectManager::RenderObjects(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->Render(renderer);
	}
}

// output first = IsIntersecting, second = collision location
std::pair<bool, SDL_FPoint> ObjectManager::IntersectCheck(std::pair<SDL_FPoint, SDL_FPoint> lineA, std::pair<SDL_FPoint, SDL_FPoint> lineB)
{
	// implementation of https://web.archive.org/web/20060911055655/http://local.wasp.uwa.edu.au/%7Epbourke/geometry/lineline2d/

	std::pair<bool, SDL_FPoint> output;

	float x1 = lineA.first.x;
	float y1 = lineA.first.y;
	float x2 = lineA.second.x;
	float y2 = lineA.second.y;
	float x3 = lineB.first.x;
	float y3 = lineB.first.y;
	float x4 = lineB.second.x;
	float y4 = lineB.second.y;

	float ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / (((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1)));
	float ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / (((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1)));

	output.first = (ua >= 0 && ua <= 1) && (ub >= 0 && ub <= 1);

	output.second.x = x1 + (ua * (x2 - x1));
	output.second.y = y1 + (ua * (y2 - y1));

	return output;
}

float ObjectManager::Lerp(float a, float b, float f)
{
	// https://stackoverflow.com/a/4353537
	return a * (1.0 - f) + (b * f);
}