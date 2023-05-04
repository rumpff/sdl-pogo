#include "GameObject.h"
#include <sstream>

void GameObject::OnCreate()
{
	// No default behaviour
}

void GameObject::OnDestroy()
{
	// No default behaviour
}

void GameObject::Tick(double deltaTime)
{
	// No default behaviour
}

void GameObject::Render(SDL_Renderer* renderer)
{
	// No default behaviour
}

std::pair < SDL_FPoint, SDL_FPoint> GameObject::GetColliderLocal()
{
	std::pair < SDL_FPoint, SDL_FPoint> line;

	line.first = { std::cos(Rotation) * (ColliderLength / 2),
		std::sin(Rotation) * (ColliderLength / 2) };
	line.second = { std::cos(Rotation + (float)M_PI) * (ColliderLength / 2), 
		std::sin(Rotation + (float)M_PI) * (ColliderLength / 2) };

	return line;
}

std::pair < SDL_FPoint, SDL_FPoint> GameObject::GetCollider()
{
	std::pair < SDL_FPoint, SDL_FPoint> line = GetColliderLocal();
	
	line.first.x += Position.x;
	line.first.y += Position.y;
	line.second.x += Position.x;
	line.second.y += Position.y;

	return line;
}

void GameObject::OnCollisionEnter(GameObject* o)
{
	// No default behaviour

	printf("collision enter\n");
}

void GameObject::OnCollision(GameObject* o)
{
	// No default behaviour

	printf("colliding...\n");
}

void GameObject::OnCollisionExit(GameObject* o)
{
	// No default behaviour

	printf("collision exit\n");
}

void GameObject::OnTriggerEnter(GameObject* o)
{
	// No default behaviour

	printf("trigger enter\n");
}

void GameObject::OnTrigger(GameObject* o)
{
	// No default behaviour

	printf("triggered...\n");
}

void GameObject::OnTriggerExit(GameObject* o)
{
	// No default behaviour

	printf("trigger exit\n");
}