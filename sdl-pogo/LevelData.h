#pragma once

#include <string>
#include <vector>

#include <SDL.h>

enum ObjectType
{
	Undefined = -1,
	Player,
	LevelFinish,
	GeometryNormal,
	GeometryHazard
};


struct LevelObject
{
	ObjectType Type;

	SDL_FPoint InitialPosition = { 0 , 0};
	float InitialRotation = 0;
	SDL_FPoint InitialVelocity = { 0,0 };
	float InitialAnguarVelocity = 0;

	float ColliderLength = 0;
};

struct LevelData
{
	std::vector<LevelObject> Objects;
	std::string Name;
};