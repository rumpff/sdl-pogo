#include "Resources.h"

void Resources::UnloadEverything()
{
	//UnLoadFonts();
}

void Resources::LoadLevels()
{	
	m_Levels.push_back(ParseLevel("Resources/Levels/level1.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level2.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level3.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level4.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level5.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level6.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level7.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level8.txt"));
	m_Levels.push_back(ParseLevel("Resources/Levels/level9.txt"));
}

void Resources::UnloadLevels()
{
	m_Levels.clear();
}

LevelData Resources::ParseLevel(std::string file)
{
	LevelData data;
	data.Name = file;

	try 
	{ 
		std::string line;
		std::ifstream levelFile(file);

		std::vector<std::string> rawLevel;

		if (levelFile.is_open())
		{
			while (getline(levelFile, line, '\n'))
			{
				if(line != "" && line[0] != '#')
					rawLevel.push_back(line);
			}

			levelFile.close();
		}

		// build data
		for (size_t i = 0; i < rawLevel.size(); i++)
		{
			std::string rawObject = rawLevel[i];
			std::vector<std::string> rawData(8);

			int index = 0;

			for (std::string::size_type c = 0; c < rawObject.size(); ++c)
			{
				if (rawObject[c] == ',')
				{
					index++;
				}
				else
				{
					rawData[index] += rawObject[c];
				}
			}

			LevelObject newObject;

			newObject.Type = (ObjectType)std::stoi(rawData[0]);
			newObject.InitialPosition = { std::stof(rawData[1]) , std::stof(rawData[2]) };
			newObject.InitialRotation = std::stof(rawData[3]) * (M_PI / 180);
			newObject.InitialVelocity = { std::stof(rawData[4]) , std::stof(rawData[5]) };
			newObject.InitialAnguarVelocity = std::stof(rawData[6]);
			newObject.ColliderLength = std::stof(rawData[7]);

			data.Objects.push_back(newObject);
		}
	}
	catch (const std::exception& e) 
	{
		printf("exception parsing level!\n");
		printf((file + "\n").c_str());
		printf(e.what());
	}
	

	return data;
}

void Resources::LoadFonts()
{
	UnLoadFonts();
	/*
	m_FontSmall = TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Small);
	m_FontDefault = TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Default);
	m_FontLarge = TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Large);
	m_FontHuge = TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Huge);
	*/
}

void Resources::UnLoadFonts()
{
	/*
	TTF_CloseFont(m_FontSmall);
	TTF_CloseFont(m_FontDefault);
	TTF_CloseFont(m_FontLarge);
	TTF_CloseFont(m_FontHuge);
	*/
}

LevelData Resources::GetLevel(int levelID)
{
	return m_Levels[levelID];
}

TTF_Font* Resources::GetFont(FontSize size)
{

	// this is real bad

	switch (size)
	{
	case Small:
		return TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Small);

	case Default:
		return TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Default);

	case Large:
		return TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Large);

	case Huge:
		return TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Huge);

	default:
		return TTF_OpenFont("Resources/Fonts/MyFont.ttf", (int)Default);
	}
}


bool Resources::HasEnding(std::string const& fullString, std::string const& ending) 
{
	// https://stackoverflow.com/a/874160
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}