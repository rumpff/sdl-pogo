#include "GameUIStates.h"

#include <sstream>

void PreGameUI::StateEnter(GameUI* m, Resources* r)
{
	m_CountdownLabel = new Label();

	m_CountdownLabel->SetText(" ");
	m_CountdownLabel->SetColor(SDL_Color{ 0xFF, 0xFF, 0xFF });
	m_CountdownLabel->SetPosition(SDL_FPoint{ Camera::SCREEN_WIDTH / 2, Camera::SCREEN_HEIGHT / 1.33, });
	m_CountdownLabel->SetFont(r->GetFont(Default));
}

void PreGameUI::StateExit()
{
	delete m_CountdownLabel;
}

void PreGameUI::StateTick(GameStats stats, double deltaTime)
{
	m_StateTimer += deltaTime;

	m_CountdownLabel->SetText(
		m_CountdownLabel->to_string_with_precision(
			Easing::EaseInExpo(m_StateTimer, 3, -3, m_StateDuration), 0));
}

void PreGameUI::StateRender(SDL_Renderer* renderer)
{
	// screen fade
	float fadeAlpha = Easing::EaseOutExpo(m_StateTimer, 255, -255, m_StateDuration);
	SDL_Rect fadeRect = { 0, 0, Camera::SCREEN_WIDTH, Camera::SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, fadeAlpha);
	SDL_RenderFillRect(renderer, &fadeRect);

	m_CountdownLabel->MakeText(renderer);
	m_CountdownLabel->Render(renderer);
}



void MidGameUI::StateEnter(GameUI* m, Resources* r)
{
	m_TimerLabel = new Label("0.00", 
		SDL_Color{ 0xFF, 0xFF, 0xFF }, 
		r->GetFont(Huge),
		SDL_FPoint{ Camera::SCREEN_WIDTH - 50, 50, });

	m_TimerLabel->SetAlign(right, top);
}

void MidGameUI::StateExit()
{
	delete m_TimerLabel;
}

void MidGameUI::StateTick(GameStats stats, double deltaTime)
{
	m_TimerLabel->SetText(m_TimerLabel->to_string_with_precision(stats.LevelTime, 3));
}

void MidGameUI::StateRender(SDL_Renderer* renderer)
{
	m_TimerLabel->MakeText(renderer);
	m_TimerLabel->Render(renderer);
}

void CompleteGameUI::StateEnter(GameUI* m, Resources* r)
{
	m_TimeLabel = new Label("0.00",
		SDL_Color{ 0xFF, 0xFF, 0xFF },
		r->GetFont(Huge),
		SDL_FPoint{ Camera::SCREEN_WIDTH / 2, Camera::SCREEN_HEIGHT / 2 });

	m_PBLabel = new Label("PB: 0.00",
		SDL_Color{ 0xFF, 0xFF, 0xFF },
		r->GetFont(Default),
		SDL_FPoint{ Camera::SCREEN_WIDTH / 2, Camera::SCREEN_HEIGHT / 1.778 });
}

void CompleteGameUI::StateExit()
{
	delete m_TimeLabel;
}

void CompleteGameUI::StateTick(GameStats stats, double deltaTime)
{
	m_StateTimer += deltaTime;
	m_TimeLabel->SetText(m_TimeLabel->to_string_with_precision(stats.LevelTime, 3));

	if (stats.LevelTime < stats.FastestTime)
	{
		m_PBLabel->SetText("You set a personal best!");
	}
	else
	{
		m_PBLabel->SetText("PB: " + m_PBLabel->to_string_with_precision(stats.FastestTime, 3));
	}
}

void CompleteGameUI::StateRender(SDL_Renderer* renderer)
{
	// TimeBG
	SDL_Rect TimeBG = { 0, Camera::SCREEN_HEIGHT / 4 + Camera::SCREEN_HEIGHT / 8 , Camera::SCREEN_WIDTH, Camera::SCREEN_HEIGHT / 4  };
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x7F);
	SDL_RenderFillRect(renderer, &TimeBG);

	m_TimeLabel->MakeText(renderer);
	m_TimeLabel->Render(renderer);

	m_PBLabel->MakeText(renderer);
	m_PBLabel->Render(renderer);

	// screen flash
	float flashAlpha = Easing::EaseOutExpo(SDL_clamp(m_StateTimer, 0, 1), 255, -255, 1);
	SDL_Rect flashRect = { 0, 0, Camera::SCREEN_WIDTH, Camera::SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, flashAlpha);
	SDL_RenderFillRect(renderer, &flashRect);
}



void FailedGameUI::StateEnter(GameUI* m, Resources* r)
{
	m_DeathLabel = new Label("YOU TRIED",
		SDL_Color{ 0xFF, 0x00, 0x00 },
		r->GetFont(Huge),
		SDL_FPoint{ Camera::SCREEN_WIDTH / 2, Camera::SCREEN_HEIGHT / 2, });
}

void FailedGameUI::StateExit()
{
	delete m_DeathLabel;
}

void FailedGameUI::StateTick(GameStats stats, double deltaTime)
{
	m_ResetTimer += deltaTime;
}

void FailedGameUI::StateRender(SDL_Renderer* renderer)
{
	// screen flash
	float flashAlpha = Easing::EaseOutExpo(m_ResetTimer, 255, -255, 0.5);
	SDL_Rect flashRect = { 0, 0, Camera::SCREEN_WIDTH, Camera::SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, flashAlpha);
	SDL_RenderFillRect(renderer, &flashRect);

	m_DeathLabel->MakeText(renderer);
	m_DeathLabel->Render(renderer);

	// screen fade
	float fadeAlpha = Easing::EaseInCirc(m_ResetTimer - 0.5f, 0, 255, 1.0f);
	SDL_Rect fadeRect = { 0, 0, Camera::SCREEN_WIDTH, Camera::SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, fadeAlpha);
	SDL_RenderFillRect(renderer, &fadeRect);
}
