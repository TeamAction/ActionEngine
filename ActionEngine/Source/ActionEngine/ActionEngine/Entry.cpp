#pragma once
#include "ActionEngine.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Audio.h"
#include "windows.h"

/*
//i added these because my computer was using my igpu not sure if they are really needed
//use nvidia graphics adapter if available
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
//use amd graphics adapter if available
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
*///not gona bother with this unless igpu cant keep up

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Renderer::Instance()->showSplash("../../../Assets/gfx/splash.png");
	SceneManager::Instance()->prepareScene("menuScene");

	for (int i = 0; i < 6; i++)
		for (int q = 0; q < 6; q++)
			Renderer::Instance()->generateSprite(0, 16 * q, 16 * i, 16, 16); //ground
	Renderer::Instance()->generateSprite(0, 16 * 7, 0, 16, 16); //background
	Renderer::Instance()->generateSprite(0, 16 * 6, 16, 16, 16); //inner ground

	Renderer::Instance()->generateSprite(1, 0, 0, 16, 16); //run frame 1
	Renderer::Instance()->generateSprite(2, 0, 0, 16, 16); //run frame 2
	Renderer::Instance()->generateSprite(3, 0, 0, 16, 16); //run frame 3
	Renderer::Instance()->generateSprite(4, 0, 0, 16, 16); //run frame 4
	Renderer::Instance()->generateSprite(5, 0, 0, 16, 16); //run frame 5
	Renderer::Instance()->generateSprite(6, 0, 0, 16, 16); //jump

	Renderer::Instance()->generateSprite(7, 0, 0, 495, 82); //title for menu

	Renderer::Instance()->generateSprite(8, 0, 0, 16, 16); //rice
	Renderer::Instance()->generateSprite(9, 0, 0, 16, 16); 
	Renderer::Instance()->generateSprite(10, 0, 0, 16, 16); 
	Renderer::Instance()->generateSprite(11, 0, 0, 16, 16); 


	Renderer::Instance()->generateAnimation("Title", animation({ 44 }));

	Renderer::Instance()->generateAnimation("BG", animation({36}));
	Renderer::Instance()->generateAnimation("groundInner", animation({37}));

	Renderer::Instance()->generateAnimation("groundLTCO", animation({ 0 }));
	Renderer::Instance()->generateAnimation("groundRTCO", animation({ 1 }));
	Renderer::Instance()->generateAnimation("groundLBCO", animation({ 6 }));
	Renderer::Instance()->generateAnimation("groundRBCO", animation({ 7 }));

	Renderer::Instance()->generateAnimation("groundLTCI", animation({ 2 }));
	Renderer::Instance()->generateAnimation("groundRTCI", animation({ 3 }));
	Renderer::Instance()->generateAnimation("groundLBCI", animation({ 8 }));
	Renderer::Instance()->generateAnimation("groundRBCI", animation({ 9 }));


	Renderer::Instance()->generateAnimation("groundL", animation({ 10 }));
	Renderer::Instance()->generateAnimation("groundR", animation({ 5 }));
	Renderer::Instance()->generateAnimation("groundU", animation({ 4}));
	Renderer::Instance()->generateAnimation("groundD", animation({ 11}));

	Renderer::Instance()->generateAnimation("spikeD", animation({ 16 }));
	Renderer::Instance()->generateAnimation("spikeU", animation({ 23 }));
	Renderer::Instance()->generateAnimation("spikeL", animation({ 24 }));
	Renderer::Instance()->generateAnimation("spikeR", animation({ 15 }));

	Renderer::Instance()->generateAnimation("groundF", animation({29}));

	Renderer::Instance()->generateAnimation("playerIdle", animation({ 38,39},0.32f));
	Renderer::Instance()->generateAnimation("playerRun", animation({40,41,42},0.32f));
	Renderer::Instance()->generateAnimation("playerJump", animation({43}));

	Renderer::Instance()->generateAnimation("riceBall", animation({45,46,47,48,47,46},3.0f));



	Audio::Instance()->LoadMusic("bgm1", "../../../Assets/AudioClips/gamemusic1.wav");
	Audio::Instance()->LoadEffect("sfx1", "../../../Assets/AudioClips/jump1.wav");

	Renderer::Instance()->Init(640,480, "../../../Assets/fonts/8bit.ttf",20);
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/tiles.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/run1.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/run2.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/run3.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/run4.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/run5.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/Ninja/jump.png");

	Renderer::Instance()->loadImageFile("../../../Assets/gfx/title.png");

	Renderer::Instance()->loadImageFile("../../../Assets/gfx/RiceBall/sushi1.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/RiceBall/sushi2.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/RiceBall/sushi3.png");
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/RiceBall/sushi4.png");
	ActionEngine::Instance()->play();
	return (0);
}
