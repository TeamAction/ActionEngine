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
	status.dwLength = sizeof(status);
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
	std::cout << status.ullTotalPhys/1024/1024 << std::endl;
	std::cout << "mb of Physical Memory " << std::endl;
	std::cout << "There is ";
	std::cout << status.ullAvailVirtual/1024/1024 << std::endl;
	std::cout << "mb of Virtual Memory " << std::endl;

	return true;
}

void Initialize::Terminate(HANDLE* hHandle)
{
	ReleaseMutex(*hHandle);
	CloseHandle(*hHandle);
}





bool Initialize::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.

	//int const drive = _getdrive();
	//struct _diskfree_t diskfree;
	//_getdiskfree(drive, &diskfree);
	//cout << diskfree.total_clusters;

	long long cluster = 0;
	long long b = 0;
	long long kb = 0;
	long long mb = 0;
	
int const drive = _getdrive();
		struct _diskfree_t diskfree;
		_getdiskfree(drive, &diskfree);
		b = diskfree.avail_clusters *diskfree.sectors_per_cluster;
		b = b * diskfree.bytes_per_sector;
		kb = b / 1024;
		mb = kb / 1024;
		//cout << b << " This Is B.\n" << endl;
		//cout << kb << " This Is KB.\n" << endl;
		cout << mb << " This Is MB.\n" << endl;

		if (mb < 300)
		{
			MessageBox(NULL, " not enough space on harddrive", NULL, MB_OK);
			return false;
		}
		return true;
	
}




	


