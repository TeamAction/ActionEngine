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

bool Initialize::CheckAvailibleMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	if (status.ullTotalPhys < physicalRAMNeeded) {
		MessageBox(NULL, "Not Enough Physical Memory", NULL, MB_OK);
		return false;
	}
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		MessageBox(NULL, "Not Enough Virtual Memory", NULL, MB_OK);
		return false;
	}
	try
	{
		char *buff = new char[virtualRAMNeeded];
	}
	catch(...)
	{
		MessageBox(NULL, "Not Enough Contiguous Memory", NULL, MB_OK);
		return false;
	}

	std::cout << "There is ";
	std::cout << status.ullTotalPhys << std::endl;
	std::cout << "kb of Physical Memory " << std::endl;
	std::cout << "There is ";
	std::cout << status.ullAvailVirtual << std::endl;
	std::cout << "kb of Virtual Memory " << std::endl;

	return true;
}

void Initialize::Terminate(HANDLE* hHandle)
{
	ReleaseMutex(*hHandle);
	CloseHandle(*hHandle);
}

 