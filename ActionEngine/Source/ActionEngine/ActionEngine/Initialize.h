#pragma once
#include "windows.h"

class Initialize
{
public:
	static bool IsOnlyInstance(const char* gameTitle, HANDLE* hHandle);
	static void Terminate(HANDLE* hHandle);
}; 