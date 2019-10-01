#include "Initialize.h"
#include <iostream>


bool Initialize::IsOnlyInstance(const char* gameTitle , HANDLE* hHandle)
{
	*hHandle = CreateMutex(NULL, TRUE, gameTitle);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		MessageBox(NULL, "Game Already Open", NULL, MB_OK);
		Initialize::Terminate(hHandle);
		return(false);
	}
	return(true);
}

bool Initialize::CheckAvailibleMemory(const DWORDLONG physicalRAMNeeded, const DWORDLONG virtualRAMNeeded)
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	if (status.ullAvailPhys < physicalRAMNeeded) {
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
		delete buff;
		buff = nullptr;
	}
	catch(...)
	{
		MessageBox(NULL, "Not Enough Contiguous Memory", NULL, MB_OK);
		return false;
	}

	std::cout << "There is ";
	std::cout << status.ullAvailPhys/1024/1024 << std::endl;
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
	delete hHandle;
	hHandle = nullptr;
}


bool Initialize::CheckStorage(const DWORDLONG diskSpaceNeeded)
{
	// Check for enough free disk space on the current disk.

	long long cluster = 0;
	long long b = 0;
	long long kb = 0;
	long long mb = 0;
	
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	b = diskfree.avail_clusters *diskfree.sectors_per_cluster;
	b = (b * diskfree.bytes_per_sector)/1024/1024;

	if (b < diskSpaceNeeded)
	{
		MessageBox(NULL, " not enough space on harddrive", NULL, MB_OK);
		return false;
	}
	return true;
	
}



const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;

void Initialize::checkSystem() {

	auto& outstream = std::cout;

	auto support_message = [&outstream](std::string isa_feature, bool is_supported) {
		outstream << isa_feature << (is_supported ? " supported" : " not supported") << std::endl;
	};

	std::cout << InstructionSet::Vendor() << std::endl;
	std::cout << InstructionSet::Brand() << std::endl;

}

