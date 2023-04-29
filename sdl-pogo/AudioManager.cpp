#include "AudioManager.h"

#include <sstream>

#include <SDL_mixer.h>

void AudioManager::Initalize()
{
	// Initialze SDL Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("mixer init errror SDL_mixer Error : %s\n", Mix_GetError());
	}
}

void AudioManager::Close()
{
	// yo, kallum
}