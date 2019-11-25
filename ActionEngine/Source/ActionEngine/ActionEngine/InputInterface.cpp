#include "InputInterface.h"
#include "tigr.h"
#include <windows.h>
#include <algorithm>


void InputInterface::fireEvent(std::vector<std::function<void()>> functions)
{
	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]();
	}
}

bool InputInterface::getEventTrigger(int key)
{
	if(key > 0)
		return GetAsyncKeyState(key);
	if (key = LEFTMOUSEBUTTON)
		return mouseB1;
	if (key = RIGHTMOUSEBUTTON)
		return mouseB3;
}

void InputInterface::prossesInput(Tigr* screen)
{
	if (GetFocus() != screen->handle)
		return;

	std::unordered_map<int, std::vector<std::function<void()>>>::iterator it = events.begin();
	tigrMouse2(screen, &mouseX, &mouseY, &mouseB1, &mouseB2, &mouseB3);
	while (it != events.end())
	{     
		if (getEventTrigger(it->first))
		{
			fireEvent(it->second);
		}
		it++;
	}

#ifdef DEBUG
	tigrKeyboardState(screen, keyboard);
#endif // DEBUG
}

void InputInterface::bindEvent(int key, std::function<void()> func)
{
	events[key].push_back(func);
}

/*void InputInterface::unBindEvent(int key, std::function<void()> func)
{
	i cannot figure out how to make this work without a complete rewrite of this event system
	there is no way i can find to compare std::functions after binding due to type erasure in bind
	//events[key].erase(std::find(events[key].begin(), events[key].end(), func), events[key].end());
}*/
