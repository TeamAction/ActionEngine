#include "Audio.h"
#include "Renderer.h"


Mix_Chunk *wave = NULL;
bool isRunning = true;
SDL_Event ev;
//Mix_Music *music = Mix_LoadMUS();

Audio::Audio()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		Renderer::Instance()->ErrorPopup("Error Audio did not initialize!");
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		Renderer::Instance()->ErrorPopup("Error Audio did not load!");
	}

	
	/*if (ev.type == SDL_QUIT)
		isRunning = false;
	else*/ if (ev.type == SDL_KEYDOWN)
	{
		switch (ev.key.keysym.sym)
		{

		case SDLK_1:
			if (Mix_PlayChannel(-1, wave, 0) == -1)
			{
				Renderer::Instance()->ErrorPopup("Error Audio did not load!");
			}
			break;
		}
	}
	//if (Mix_PlayMusic(music, -1) == -1) {
	//	Renderer::Instance()->ErrorPopup("Error Audio did not load!");
	//}

	while (Mix_PlayingMusic());
}




void Audio::loadClip(std::string beatbox, std::string filePath)
{
	//Mix_Chunk *wave = Mix_LoadWAV("505528__dbairsoft__beatbox1");


	Mix_Chunk *wave = Mix_LoadWAV("../../../Assets/AudioClips/505528__dbairsoft__beatbox1", filePath);
	if (wave == NULL) {
		Renderer::Instance()->ErrorPopup("Error! did not load!");
	}

	/*music = Mix_LoadMUS(MUS_PATH);
	if (music == NULL) {
		Renderer::Instance()->ErrorPopup("Error! did not load!");
	}*/
}

Audio::~Audio()
{
	
	// clean up our resources
	Mix_FreeChunk(wave);
	//Mix_FreeMusic(music);

	wave = nullptr;

	// quit SDL_mixer
	Mix_CloseAudio();
	
	
	////clean up our resourses
	//Mix_FreeChunk(wave);
	//Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");

	//wave = nullptr;

	///*Mix_FreeMusic(music);
	//Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");*/
	////quit sdl mixer
	//Mix_Quit();
	//Mix_CloseAudio();

	
}
