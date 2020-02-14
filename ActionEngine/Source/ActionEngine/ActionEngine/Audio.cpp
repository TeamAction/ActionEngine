#include "Audio.h"
#include "Renderer.h"

Mix_Chunk *wave = Mix_LoadWAV("505528__dbairsoft__beatbox1");

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

	

	//if (Mix_PlayMusic(music, -1) == -1) {
	//	Renderer::Instance()->ErrorPopup("Error Audio did not load!");
	//}

	while (Mix_PlayingMusic());
}

bool isRunning = true;
SDL_Event ev;


void Audio::loadClip(std::string beatbox, std::string filePath)
{
	if (ev.type == SDL_QUIT)
		isRunning = false;
	else if (ev.type == SDL_KEYDOWN)
	{
		switch (ev.key.keysym.sym)
		{

		case SDLK_1:
			Mix_PlayChannel(-1, wave, 0);
			break;
		}
	}

	/*wave = Mix_LoadWAV(filePath, "../../../Assets/AudioClips/505528__dbairsoft__beatbox1");
	if (wave == NULL) {
		Renderer::Instance()->ErrorPopup("Error! did not load!");
	}*/

	/*music = Mix_LoadMUS(MUS_PATH);
	if (music == NULL) {
		Renderer::Instance()->ErrorPopup("Error! did not load!");
	}*/
}

Audio::~Audio()
{
	//clean up our resourses
	Mix_FreeChunk(wave);
	Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");

	wave = nullptr;

	/*Mix_FreeMusic(music);
	Renderer::Instance()->ErrorPopup("Error! Audio file did not load!");*/
	//quit sdl mixer
	Mix_Quit();
	Mix_CloseAudio();

	
}
