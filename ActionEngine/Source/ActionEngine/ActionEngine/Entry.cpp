#pragma once
#include "ActionEngine.h"
#include "Renderer.h"
#include "SceneManager.h"
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
	SceneManager::Instance()->prepareScene("testScene1"); 
	Renderer::Instance()->generateSprite(0, 16 * 5, 16 * 8, 16, 16);
	Renderer::Instance()->generateSprite(0, 16 * 6, 16 * 8, 16, 16);
	Renderer::Instance()->generateSprite(0, 16 * 7, 16 * 8, 16, 16);
	Renderer::Instance()->generateSprite(0, 16 * 8, 16 * 8, 16, 16);

	Renderer::Instance()->generateSprite(0, 16 * 7, 16 * 9, 16, 16);
	Renderer::Instance()->generateSprite(0, 0, 16 * 8, 400, 16);


	Sleep(1500); //give time to show splash
	Renderer::Instance()->Init(640,480, "../../../Assets/fonts/FreeSans.ttf",20);
	Renderer::Instance()->loadImageFile("../../../Assets/gfx/cave.png");

	ActionEngine::Instance()->play();
	return (0);
}
