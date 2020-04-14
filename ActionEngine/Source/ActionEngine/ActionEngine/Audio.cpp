#include "Audio.h"
#include "Renderer.h"
#include "InputManager.h"


Mix_Chunk* wave = NULL;
bool isRunning = true;
SDL_Event ev;


Audio* Audio::s_Instance = nullptr;

// Init audio system
Audio::Audio()
{

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		Renderer::Instance()->ErrorPopup("Error Audio did not initialize!");
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		Renderer::Instance()->ErrorPopup("Error Audio did not load!");
	}
}

// Music

void Audio::PlayMusic(std::string id) {
	
	if (Mix_PlayMusic(m_MusicMap[id], -1) == -1)
		std::cerr << Mix_GetError() << ": " << id << std::endl;

	if (!Mix_PlayingMusic()) {

		Mix_PlayMusic(m_MusicMap[id], -1);
	}


}

void Audio::LoadMusic(std::string id, std::string source) {
	Mix_Music* bgm = Mix_LoadMUS(source.c_str());
	if (bgm != nullptr)
		m_MusicMap[id] = bgm;
	else
		std::cerr << Mix_GetError() << ": " << source << std::endl;
}

// Chunk

void Audio::PlayEffect(std::string id) {
	
	if (Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1)
		std::cerr << Mix_GetError() << ": " << id << std::endl;
}
		
void Audio::LoadEffect(std:: string id, std::string source) {
	Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
	if (effect != nullptr)
		m_EffectMap[id] = effect;
	else
		std::cerr << Mix_GetError() << ": " << source << std::endl;
}

// Clean memory of used sound files
void Audio::Clean() {

	for (MusicMap::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it++)
		Mix_FreeMusic(it->second);

	for (EffectMap::iterator it = m_EffectMap.begin(); it != m_EffectMap.end(); it++)
		Mix_FreeChunk(it->second);
	m_MusicMap.clear();
	m_EffectMap.clear();
	std::cout << "Sound system cleaned!" << std::endl;

}







//Audio::Audio()
//{
//	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//		Renderer::Instance()->ErrorPopup("Error Audio did not initialize!");
//	}
//
//	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
//	{
//		Renderer::Instance()->ErrorPopup("Error Audio did not load!");
//	}
//
//
//	/*if (ev.type == SDL_QUIT)
//		isRunning = false;
//	else*/ if (ev.type == SDL_KEYDOWN)
//	{
//		switch (ev.key.keysym.sym)
//		{
//
//		case SDLK_p:
//			if (Mix_PlayingMusic())
//				Mix_PlayMusic(bgm, -1);
//			{
//				Renderer::Instance()->ErrorPopup("Error Audio did not load!");
//			}
//			break;
//		}
//	}
//	//if (Mix_PlayMusic(music, -1) == -1) {
//	//	Renderer::Instance()->ErrorPopup("Error Audio did not load!");
//	//}
//
//	while (Mix_PlayingMusic());
//}



//void Audio::loadClip(std::string beatbox, std::string filePath)
//{
//	//Mix_Chunk *wave = Mix_LoadWAV("505528__dbairsoft__beatbox1");
//
//
//	Mix_Chunk *wave = Mix_LoadWAV("../../../Assets/AudioClips/505528__dbairsoft__beatbox1", filePath);
//	if (wave == NULL) {
//		Renderer::Instance()->ErrorPopup("Error! did not load!");
//	}
//
//	/*music = Mix_LoadMUS(MUS_PATH);
//	if (music == NULL) {
//		Renderer::Instance()->ErrorPopup("Error! did not load!");
//	}*/
//}

//Audio::~Audio()
//{
//	
//	// clean up our resources
//	Mix_FreeChunk(wave);
//	//Mix_FreeMusic(music);
//
//	wave = nullptr;
//
//	// quit SDL_mixer
//	Mix_CloseAudio();
//	
//	
//	////clean up our resourses
//	//Mix_FreeChunk(wave);
//	//Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");
//
//	//wave = nullptr;
//
//	///*Mix_FreeMusic(music);
//	//Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");*/
//	////quit sdl mixer
//	//Mix_Quit();
//	//Mix_CloseAudio();
//
//	
//}
