#pragma once
#include <iostream>
#include "Initialize.h"


int main()
{
	Initialize::checkSystem();

	HANDLE hHandle;
	if (!Initialize::IsOnlyInstance("MyGame",&hHandle))
		return(0);

	while (true)
	{
		
	}

	Initialize::Terminate(&hHandle);
	return (0);
}
 