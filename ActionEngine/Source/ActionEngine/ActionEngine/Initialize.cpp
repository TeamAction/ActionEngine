#include "Initialize.h"
#include <iostream>

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

const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;

void Initialize::checkSystem() {

	auto& outstream = std::cout;

	auto support_message = [&outstream](std::string isa_feature, bool is_supported) {
		outstream << isa_feature << (is_supported ? " supported" : " not supported") << std::endl;
	};

	std::cout << InstructionSet::Vendor() << std::endl;
	std::cout << InstructionSet::Brand() << std::endl;

}

 