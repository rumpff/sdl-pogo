#include "GameManager.h"

#include <string>

void GameManager::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		m_Camera = new Camera();
		m_Camera->Initialize();

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}

		// Initialze SDL_ttf
		if (TTF_Init() == -1)
		{
			printf("oopsiewoopsie something went wrong initializing SDL_ttf SDL_ttf Error: %s\n", TTF_GetError());
		}

		m_AudioManager = new AudioManager();
		m_AudioManager->Initialize();
	}

	m_ResourceLoader = new ResourceLoader();

	// Dummy data
	LevelData dummyData;

	LevelObject dummyPlayer;

	dummyPlayer.Type = Player;
	dummyPlayer.InitialPosition = { 1280.0f / 2.0f, 720.0f / 2.0f };
	dummyPlayer.InitialRotation = -M_PI / 2.0f;

	dummyData.Objects.push_back(dummyPlayer);

	float wallSize = 300;
	for (int i = 0; i < 4; i++)
	{
		LevelObject dummyWall;
		dummyWall.Type = GeometryNormal;
		if (i == 3)
		{
			dummyWall.ColliderLength = wallSize;

			dummyWall.InitialRotation = i * ((M_PI * 2) / 4) + (M_PI / 8);
			dummyWall.InitialPosition =
			{
				(1280 / 2) - cosf(dummyWall.InitialRotation - (M_PI / 2)) * (wallSize / 1.5f),
				(720 / 2) - sinf(dummyWall.InitialRotation - (M_PI / 2)) * (wallSize / 1.5f)
			};

			dummyData.Objects.push_back(dummyWall);

			dummyWall.Type = LevelFinish;
		}
			

		dummyWall.ColliderLength = wallSize;

		dummyWall.InitialRotation = i * ((M_PI * 2) / 4) + (M_PI / 8);
		dummyWall.InitialPosition =
		{
			(1280 / 2) - cosf(dummyWall.InitialRotation - (M_PI / 2)) * (wallSize / 2),
			(720 / 2) - sinf(dummyWall.InitialRotation - (M_PI / 2)) * (wallSize / 2)
		};

		dummyData.Objects.push_back(dummyWall);
	}

	// Load first level
	ChangeLevel(new GameLevelManager(), dummyData);

	Manager::Initialize();
}

void GameManager::Close()
{
	// Close managers
	m_CurrentLevel->Close(); delete m_CurrentLevel;
	m_AudioManager->Close(); delete m_AudioManager;
	m_ResourceLoader->UnloadEverything(); delete m_ResourceLoader;
	m_Camera->Close(); delete m_Camera;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

LevelManager* GameManager::ChangeLevel(LevelManager* newLevel)
{
	// Current level should only be null when the game starts
	if (m_CurrentLevel != 0)
	{
		m_CurrentLevel->Close();
		delete m_CurrentLevel;
	}

	m_CurrentLevel = newLevel;
	m_CurrentLevel->Initialize();

	return m_CurrentLevel;
}

LevelManager* GameManager::ChangeLevel(LevelManager* newLevel, LevelData data)
{
	ChangeLevel(newLevel)->LoadData(data);
	return m_CurrentLevel;
}

void GameManager::Game()
{
	//Start up SDL and create window
	if (!IsInitialzed())
	{
		printf("trying to run gameloop before manager initalization!\n");
		return;
	}

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	// deltatime implementation from https://gamedev.stackexchange.com/a/110831
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;


	//While application is running
	while (!quit)
	{
		// Update deltatime
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		m_CurrentLevel->Tick(deltaTime);
		m_Camera->Render(m_CurrentLevel);
	}
}