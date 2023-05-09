#include "Label.h"

Label::Label()
{

}

Label::Label(std::string text, SDL_Color color, TTF_Font* font, SDL_FPoint pos)
{
	SetText(text);
	SetColor(color);
	SetFont(font);
	SetPosition(pos);
}

Label::~Label()
{
	//TTF_CloseFont(m_Font);
	//Free();
}

void Label::Free()
{
	if (m_Texture != 0)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = 0;
	}
}

void Label::SetPosition(SDL_FPoint pos)
{
	m_Position = pos;
}

void Label::SetColor(SDL_Color color)
{
	m_Color = color;
}

void Label::SetText(std::string text)
{
	m_Text = text;
}

void Label::SetFont(TTF_Font* font)
{
	m_Font = font;
}

void Label::SetAlign(TextAlign horizontal, TextAlign vertical)
{
	m_HorAlign = horizontal;
	m_VerAlign = vertical;
}

void Label::MakeText(SDL_Renderer* renderer)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Blended(m_Font, m_Text.c_str(), m_Color);

	m_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	m_Size.x = textSurface->w;
	m_Size.y = textSurface->h;

	SDL_FreeSurface(textSurface);
	textSurface = 0;
}

void Label::Render(SDL_Renderer* renderer)
{
	SDL_Rect renderQuad = { GetPosition().x, GetPosition().y, m_Size.x, m_Size.y};
	SDL_RenderCopy(renderer, m_Texture, NULL, &renderQuad);
}

SDL_FPoint Label::GetSize()
{
	return m_Size;
}

SDL_FPoint Label::GetPosition()
{
	return
	{
		m_Position.x - (m_Size.x * ((float)m_HorAlign / 10.0f)),
		m_Position.y - (m_Size.y * ((float)m_VerAlign / 10.0f))
	};
}
