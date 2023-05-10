#include "Camera.h"

void Camera::Initialize()
{
	//Create window
	m_Window = SDL_CreateWindow("SDL Pogo", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_Window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}

	// Create renderer
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == NULL)
	{
		printf("something went wrong while creating the renderer lmao");
	}

	// Init render color
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

	// Get window surface
	m_ScreenSurface = SDL_GetWindowSurface(m_Window);
}

void Camera::Close()
{
	//Destroy window
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;
}

void Camera::Render(LevelManager* currentLevel, UI* ui)
{
	// Clear screen
	
	SDL_SetRenderDrawColor(m_Renderer, 0x0C, 0x13, 0x4F, 0xFF);
	SDL_RenderClear(m_Renderer);

	// Render stuff here
	if(currentLevel != 0)
		currentLevel->Render(m_Renderer);

	if (ui != 0)
		ui->Render(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}