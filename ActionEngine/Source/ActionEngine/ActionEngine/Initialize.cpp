#include "Initialize.h"

bool Initialize::IsOnlyInstance(const char* gameTitle)
{
	//const char szUniqueNamedMutex[] = gameTitle;
	HANDLE hHandle = CreateMutex(NULL, TRUE, gameTitle);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		MessageBox(NULL, "Game Already Open", NULL, MB_OK);
		return(false);
	}
	return(true);
}

static void Terminate()
{
	//ReleaseMutex(hHandle);
	//CloseHandle(hHandle);
}

 