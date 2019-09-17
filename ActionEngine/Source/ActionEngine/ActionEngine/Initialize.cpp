#include "Initialize.h"

bool Initialize::IsOnlyInstance(const char* gameTitle , HANDLE* hHandle)
{
	*hHandle = CreateMutex(NULL, TRUE, gameTitle);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		MessageBox(NULL, "Game Already Open", NULL, MB_OK);
		return(false);
	}
	return(true);
}

void Initialize::Terminate(HANDLE* hHandle)
{
	ReleaseMutex(*hHandle);
	CloseHandle(*hHandle);
}

 