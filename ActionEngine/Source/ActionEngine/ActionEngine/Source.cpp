#pragma once
#include <iostream>
#include "Initialize.h"

int main()
{
	HANDLE hHandle;
	if (!Initialize::IsOnlyInstance("MyGame",&hHandle))
		return(0);

	while (true)
	{
		std::cout << "Hello World" << std::endl;
	}

	Initialize::Terminate(&hHandle);
	return (0);
}
 