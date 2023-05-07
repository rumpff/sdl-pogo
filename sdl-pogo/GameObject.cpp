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

void GameObject::UpdatePrev()
{
	PositionPrev = Position;
	RotationPrev = Rotation;
}

std::pair< SDL_FPoint, SDL_FPoint> GameObject::CalcLine(float angle, float length)
{
	std::pair < SDL_FPoint, SDL_FPoint> line;

	line.first = { std::cos(angle) * (length / 2),
	std::sin(angle) * (length / 2) };
	line.second = { std::cos(angle + (float)M_PI) * (length / 2),
		std::sin(angle + (float)M_PI) * (length / 2) };

	return line;
}

std::pair < SDL_FPoint, SDL_FPoint> GameObject::GetColliderLocal()
{
	return CalcLine(Rotation, m_ColliderLength);
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
std::pair < SDL_FPoint, SDL_FPoint> GameObject::GetColliderPrevLocal()
{
	return CalcLine(RotationPrev, m_ColliderLength);
}
std::pair < SDL_FPoint, SDL_FPoint> GameObject::GetColliderPrev()
{
	std::pair < SDL_FPoint, SDL_FPoint> line = GetColliderPrevLocal();

	line.first.x += PositionPrev.x;
	line.first.y += PositionPrev.y;
	line.second.x += PositionPrev.x;
	line.second.y += PositionPrev.y;

	return line;
}

void GameObject::OnCollisionEnter(Collision c)
{
	// No default behaviour

	printf("collision enter\n");
}

void GameObject::OnCollision(Collision c)
{
	// No default behaviour

	printf("colliding...\n");
}

void GameObject::OnCollisionExit(Collision c)
{
	// No default behaviour

	printf("collision exit\n");
}

void GameObject::OnTriggerEnter(Collision c)
{
	// No default behaviour

	printf("trigger enter\n");
}

void GameObject::OnTrigger(Collision c)
{
	// No default behaviour

	printf("triggered...\n");
}

void GameObject::OnTriggerExit(Collision c)
{
	// No default behaviour

	printf("trigger exit\n");
}