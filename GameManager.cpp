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

	Resources* resources = new Resources();
	resources->LoadFonts();
	resources->LoadLevels();

	// Load first level
	ChangeLevel(new GameLevelManager(), resources->GetLevel(0));

	Manager::Initialize(resources);
}

void GameManager::Close()
{
	// Close managers
	m_CurrentLevel->Close(); delete m_CurrentLevel;
	m_AudioManager->Close(); delete m_AudioManager;
	m_Resources->UnloadEverything(); delete m_Resources;
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
	m_CurrentLevel->Initialize(m_Resources);

	return m_CurrentLevel;
}

LevelManager* GameManager::ChangeLevel(LevelManager* newLevel, LevelData data)
{
	ChangeLevel(newLevel)->LoadData(data);
	return m_CurrentLevel;
}

void GameManager::LevelSwitcher()
{
	// this is bad
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_1])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(0));
	}
	else if (currentKeyStates[SDL_SCANCODE_2])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(1));
	}
	else if (currentKeyStates[SDL_SCANCODE_3])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(2));
	}
	else if (currentKeyStates[SDL_SCANCODE_4])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(3));
	}
	else if (currentKeyStates[SDL_SCANCODE_5])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(4));
	}
	else if (currentKeyStates[SDL_SCANCODE_6])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(5));
	}
	else if (currentKeyStates[SDL_SCANCODE_7])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(6));
	}
	else if (currentKeyStates[SDL_SCANCODE_8])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(7));
	}
	else if (currentKeyStates[SDL_SCANCODE_9])
	{
		ChangeLevel(new GameLevelManager(), m_Resources->GetLevel(8));
	}
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
		
		// janky
		LevelSwitcher();

		m_CurrentLevel->Tick(deltaTime);
		m_Camera->Render(m_CurrentLevel, m_CurrentLevel->GetUI());
	}
}