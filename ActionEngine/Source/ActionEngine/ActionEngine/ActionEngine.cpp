#define PHYSAC_IMPLEMENTATION
#include "ActionEngine.h"

ActionEngine* ActionEngine::s_pInstance = 0;


ActionEngine::ActionEngine()
{
	engineActive = true;
	screen = tigrWindow(320, 240, "Hello", 8);
}


ActionEngine::~ActionEngine()
{
	delete s_pInstance;
	s_pInstance = nullptr;
	tigrFree(screen);
	screen = nullptr;
}

bool ActionEngine::isGameActive()
{
	return engineActive && !tigrClosed(screen);
}

void ActionEngine::tick()
{
	frameTime = tigrTime();
	for (int i = 0; i < activeActors.size(); i++)
	{
		activeActors[i].tick();
	}
}

void ActionEngine::draw()
{
	tigrClear(screen, tigrRGB(0x80, 0x90, 0xa0));
	tigrPrint(screen, tfont, 120, 110, tigrRGB(0xff, 0xff, 0xff), "Hello, world.");
	tigrUpdate(screen);
}
