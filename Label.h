#pragma once

#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

enum TextAlign
{
	left = 0,
	right = 10,
	center = 5,
	top = 0,
	middle = 5,
	bottom = 10
};

class Label
{
public:
	// Init with defaults
	Label();
	Label(std::string text, SDL_Color color, TTF_Font* font, SDL_FPoint pos);

	~Label();

	void Free();
	
	void SetPosition(SDL_FPoint pos);
	void SetColor(SDL_Color color);
	void SetText(std::string text);
	void SetFont(TTF_Font* font);
	void SetAlign(TextAlign horizontal, TextAlign vertical);

	void MakeText(SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);

	SDL_FPoint GetSize();

	/// <summary>
	/// Calculate position takign align in account
	/// </summary>
	/// <returns>Aligned position</returns>
	SDL_FPoint GetPosition();

	template <typename T>
	std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		// https://stackoverflow.com/a/16606128
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << a_value;
		return std::move(out).str();
	}

private:
	SDL_Texture* m_Texture = 0;
	TTF_Font* m_Font = 0;
	SDL_FPoint m_Position;
	SDL_FPoint m_Size;
	SDL_Color m_Color;
	std::string m_Text = " ";

	TextAlign m_HorAlign = center;
	TextAlign m_VerAlign = middle;
};