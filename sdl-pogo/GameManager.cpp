#include "GameManager.h"

void GameManager::Initalize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Create renderer
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_Renderer == NULL)
			{
				printf("something went wrong while creating the renderer lmao");
			}
			else
			{
				// init render color
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

				// Initialze SDL Mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("mixer init errror SDL_mixer Error : %s\n", Mix_GetError());
				}

				//Get window surface
				m_ScreenSurface = SDL_GetWindowSurface(m_Window);
			}
		}
	}

	// Initialzie Managers
	m_ResourceLoader = new ResourceLoader();
	m_AudioManager = new AudioManager();

	m_AudioManager->Initalize();

	Manager::Initalize();
}

void GameManager::Close()
{
	//Destroy window
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	// Close 

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
	m_CurrentLevel->Initalize(1);
}

void GameManager::GameLoop()
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

		// Clear screen
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(m_Renderer);

		SDL_RenderPresent(m_Renderer);
	}
}