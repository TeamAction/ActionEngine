#pragma once
#include "ActionEngine.h"
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
	ActionEngine::Instance()->play();
	return (0);
}
