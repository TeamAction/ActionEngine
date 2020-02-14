#pragma once
#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>


class Audio
{
public:
	Audio();
	std::unordered_map<std::string, Mix_Chunk*> clipList;
	std::unordered_map<std::string, Mix_Music*> musicList;

	void loadClip(std::string beatbox, std::string filePath);
	~Audio();
};

