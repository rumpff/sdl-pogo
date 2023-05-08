#include "ResourceLoader.h"

void ResourceLoader::UnloadEverything()
{
	// Houdoe
}

void ResourceLoader::LoadLevels()
{
	//ParseLevel();
}

LevelData ResourceLoader::ParseLevel(std::string file)
{
	LevelData data;

	try 
	{ 
		std::string line;
		std::ifstream levelFile(file);

		std::vector<std::string> rawLevel;

		if (levelFile.is_open())
		{
			while (getline(levelFile, line, '\n'))
			{
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
		printf("exception parsing level!n");
		printf(e.what());
	}
	

	return data;
}


bool ResourceLoader::HasEnding(std::string const& fullString, std::string const& ending) 
{
	// https://stackoverflow.com/a/874160
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}