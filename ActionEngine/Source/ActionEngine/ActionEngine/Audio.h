#pragma once


#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <map>

using EffectMap = std::map<std::string, Mix_Chunk*>;
using MusicMap = std::map<std::string, Mix_Music*>;

class Audio
{
public:

	void Clean();

	void PlayMusic();
	void LoadMusic(std::string id, std::string source);

	void PlayEffect();
	void LoadEffect(std::string id, std::string source);

	inline static Audio* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Audio(); }

	//Audio();
	/*std::unordered_map<std::string, Mix_Chunk*> clipList;
	std::unordered_map<std::string, Mix_Music*> musicList;*/

	//void loadClip(std::string beatbox, std::string filePath);
	//~Audio();

private:
	Audio();
	MusicMap m_MusicMap;
	EffectMap m_EffectMap;
	static Audio* s_Instance;
};

