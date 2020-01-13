#pragma once
#include "ActionEngine.h"
#include "windows.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	ActionEngine::Instance()->play();
	return (0);
}
 