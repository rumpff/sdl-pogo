#pragma once

#include <fstream>
#include <string>

#include <SDL.h>

#include "LevelData.h"

class ResourceLoader
{
public:
	void UnloadEverything();

	void LoadLevels();
	LevelData ParseLevel(std::string file);

private:

	bool HasEnding(std::string const& fullString, std::string const& ending);
};