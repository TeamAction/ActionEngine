#include "ActionEngine.h"



ActionEngine::ActionEngine()
{
	engineActive = true;
}


ActionEngine::~ActionEngine()
{
}

bool ActionEngine::active()
{
	return engineActive;
}

void ActionEngine::tick()
{
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i].tick();
	}
}
