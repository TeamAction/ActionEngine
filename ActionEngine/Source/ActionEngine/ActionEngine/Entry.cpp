#pragma once
#include <iostream>
#include "Initialize.h"
#include "ActionEngine.h"


int main()
{
	HANDLE hHandle;
	if (!Initialize::IsOnlyInstance("MyGame",&hHandle))
		return(0);
	
	if (!Initialize::CheckAvailibleMemory(300000, 300000)) // memory in kb
		return(0);

	if (!Initialize::CheckStorage(300)) // memory in mb
		return (0);

	Initialize::checkSystem();

	std::unique_ptr<ActionEngine> game(new ActionEngine());
	while (game->active())
	{
		game->tick();
	}

	Initialize::Terminate(&hHandle);
	return (0);
}
 