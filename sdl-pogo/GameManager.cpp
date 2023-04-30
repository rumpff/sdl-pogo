#include "GameManager.h"

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

	// Load first level
	ChangeLevel(new GameLevelManager());

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

void GameManager::ChangeLevel(LevelManager* newLevel)
{
	// Current level should only be null when the game starts
	if (m_CurrentLevel != 0)
	{
		m_CurrentLevel->Close();
		delete m_CurrentLevel;
	}

	m_CurrentLevel = newLevel;
	m_CurrentLevel->Initialize();
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

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		m_CurrentLevel->Tick(1.0 / 60.0);
		m_Camera->Render(m_CurrentLevel);
	}
}