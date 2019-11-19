#include "InputInterface.h"
#include "tigr.h"
#include <windows.h>

#define DEBUG

void InputInterface::prossesInput(Tigr* screen)
{
	std::unordered_map<int, std::vector<std::function<void()>>>::iterator it = events.begin();
#ifdef DEBUG
	tigrKeyboardState(screen, keyboard);
#endif // DEBUG
	tigrMouse2(screen, &mouseX, &mouseY, &mouseB1, &mouseB2, &mouseB3);


	while (it != events.end())
	{     
		if (GetAsyncKeyState(it->first))
		{
			for (int i = 0; i < it->second.size(); i++)
			{
				it->second[i]();
			}
		}
		it++;
	}
}

void InputInterface::bindEvent(int key, std::function<void()> func)
{
	events[key].push_back(func);
}
