#pragma once
#include "windows.h"

static class Initialize
{
public:
	static bool IsOnlyInstance(const char* gameTitle);
	static void Terminate();
}; 