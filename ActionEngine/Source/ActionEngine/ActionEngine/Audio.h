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
	void PlayMusic(std:: string id);
	void LoadMusic(std::string id, std::string source);
	void stopMusic();

	void PlayEffect(std:: string id);
	void LoadEffect(std::string id, std::string source);

	inline static Audio* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Audio(); }

	

private:
	Audio();
	~Audio();
	MusicMap m_MusicMap;
	EffectMap m_EffectMap;
	static Audio* s_Instance;
};

