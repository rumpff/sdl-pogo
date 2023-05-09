#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "LevelData.h"

enum FontSize
{
	Small = 16,
	Default = 28,
	Large = 36,
	Huge = 48,
};

class Resources
{
public:
	void UnloadEverything();
	void LoadLevels();
	void LoadFonts();
	void UnLoadFonts();
	LevelData ParseLevel(std::string file);

	TTF_Font* GetFont(FontSize size);
	LevelData GetLevel(int levelID);

private:
	bool HasEnding(std::string const& fullString, std::string const& ending);
	std::vector<LevelData> m_Levels;

};