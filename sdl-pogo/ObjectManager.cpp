#include "ObjectManager.h"

void ObjectManager::Initialize()
{
	CreateObject(new PlayerObject());
	CreateObject(new GeometryObject());
}

void ObjectManager::Close()
{
	// Later he
}

void ObjectManager::CreateObject(GameObject* newObject)
{
	m_GameObjects.push_back(newObject);
	newObject->OnCreate();
}

void ObjectManager::GameTick(double deltaTime)
{
	for (size_t i = 0; i < m_GameObjects.size(); i++)
	{
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

		// Modify Velocities
		velocity.x += gravity.x;
		velocity.y += gravity.y;

		// Apply Velocities
		object->Velocity = velocity;

		// Move Object
		object->PositionPrev = object->Position;
		object->Position.x += object->Velocity.x;
		object->Position.y += object->Velocity.y;

		// Check for intersection
		for (size_t j = 0; j < m_GameObjects.size(); j++)
		{
			// Skip self
			if (i == j)
				continue;

			GameObject* otherObject = m_GameObjects[j];

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

			// Find line end to snap object to
			SDL_FPoint anchor;
			std::pair < SDL_FPoint, SDL_FPoint> objectColliderLocal = object->GetColliderLocal();

			float distToFirst = std::hypotf(object->Velocity.x - objectColliderLocal.first.x, object->Velocity.y - objectColliderLocal.first.y );
			float distToSecond = std::hypotf(object->Velocity.x - objectColliderLocal.second.x, object->Velocity.y - objectColliderLocal.second.y);

			if(distToSecond < distToFirst) { anchor = objectColliderLocal.second; }
			else { anchor = objectColliderLocal.first; }

			SDL_FPoint newPos
			{
				intersect.second.x - anchor.x,
				intersect.second.y - anchor.y,
			};

			object->Position = newPos;
			object->Velocity = { 0, 0 };

			object->OnCollision();
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