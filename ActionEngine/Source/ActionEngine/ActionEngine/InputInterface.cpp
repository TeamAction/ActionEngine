#include "InputInterface.h"
#include "tigr.h"
#include <windows.h>


void InputInterface::fireEvent(std::vector<std::function<void()>> functions)
{
	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]();
	}
}

void InputInterface::prossesInput(Tigr* screen)
{
	if (GetFocus() != screen->handle)
		return;

	std::unordered_map<int, std::vector<std::function<void()>>>::iterator it = events.begin();
#ifdef DEBUG
	tigrKeyboardState(screen, keyboard);
#endif // DEBUG
	tigrMouse2(screen, &mouseX, &mouseY, &mouseB1, &mouseB2, &mouseB3);
	while (it != events.end())
	{     
		if (GetAsyncKeyState(it->first))
		{
			fireEvent(it->second);
		}
		it++;
	}
}

void InputInterface::bindEvent(int key, std::function<void()> func)
{
	events[key].push_back(func);
}
