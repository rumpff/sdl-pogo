#pragma once

class GameObject;

struct Collision
{
	GameObject* Object = 0;
	int ColliderAnchor = 0;
	SDL_FPoint ImpactVelocity;
};