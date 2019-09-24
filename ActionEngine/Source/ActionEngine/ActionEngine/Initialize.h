#pragma once
#include "windows.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

class Initialize
{
public:
	static bool IsOnlyInstance(const char* gameTitle, HANDLE* hHandle);
	static bool CheckAvailibleMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded);
	static void Terminate(HANDLE* hHandle);
	static bool CheckStorage(const DWORDLONG diskSpaceNeeded);
}; 