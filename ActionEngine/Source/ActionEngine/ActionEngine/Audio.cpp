#include "Audio.h"
#include "Renderer.h"
#include "InputManager.h"


Mix_Chunk* wave = NULL;
bool isRunning = true;
SDL_Event ev;




//Mix_Music *music = Mix_LoadMUS();

Audio* Audio::s_Instance = nullptr;

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

void Audio::PlayMusic() {
	Mix_Music* bgm = Mix_LoadMUS("../../../Assets/AudioClips/gamemusic1.wav");

	if (!Mix_PlayingMusic()) {

		Mix_PlayMusic(bgm, -1);
	}


}

//void Audio::LoadMusic(std::string id, std::string source) {
//	Mix_Music* bgm = Mix_LoadMUS("../../../Assets/AudioClips/505528__dbairsoft__beatbox1");
//	m_MusicMap[id] = bgm;
//	//else
//	//	Renderer::Instance()->ErrorPopup("Error Audio did not LOAD!");
//}

// Chunk

void Audio::PlayEffect() {
	Mix_Chunk* sfx1 = Mix_LoadWAV("../../../Assets/AudioClips/jump1.wav");

				Mix_PlayChannel(-1, sfx1, 0);

}
		
	

//void Audio::PlayEffect(std::string id) {
//	if(Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1)
//		Renderer::Instance()->ErrorPopup("Error Play Effect did not Play!");
//}

//void Audio::LoadEffect(std::string id, std::string source) {
//	Mix_Chunk* effect = Mix_LoadWAV("../../../Assets/AudioClips/505528__dbairsoft__beatbox1");
//	if (effect != nullptr)
//		m_EffectMap[id] = effect;
//	else
//		Renderer::Instance()->ErrorPopup("Error did not Load Effect!");
//}

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
