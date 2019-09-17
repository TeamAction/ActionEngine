#pragma once
#include "windows.h"
#include <iostream>

class Initialize
{
public:
	static bool IsOnlyInstance(const char* gameTitle, HANDLE* hHandle);
	static bool CheckAvailibleMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	static void Terminate(HANDLE* hHandle);
}; 