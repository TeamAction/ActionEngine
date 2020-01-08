#include "EventManager.h"
#include "tigr.h"
#include <windows.h>
#include <algorithm>


EventManager* EventManager::s_pInstance = 0;

void EventManager::fireEvent(std::string name)
{
	removePendingEvents();
	EventCallbacks* currentEvent = &events[name];
	std::unordered_map<int, std::function<void()>>::iterator it = currentEvent->callbacks.begin();
	while (it != currentEvent->callbacks.end())
	{
		it->second();
		it++;
	}
}

/*void EventManager::prossesInput(Tigr* screen)
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
}*/

EventId EventManager::bindEvent(std::string eventName, std::function<void()> func)
{
	EventId newEvent;
	newEvent.name = eventName;
	do{
		newEvent.idNumber = rand();
	} while (events[eventName].callbacks.count(newEvent.idNumber) > 0);

	events[eventName].callbacks[newEvent.idNumber] = func;
	return newEvent;
}

void EventManager::unBindEvent(EventId id)
{
	pendingRemoval.push_back(id);
}

void EventManager::removePendingEvents()
{
	for (int i = 0; i < pendingRemoval.size(); i++)
	{
		events[pendingRemoval[i].name].callbacks.erase(pendingRemoval[i].idNumber);
	}
	pendingRemoval.clear();
}
