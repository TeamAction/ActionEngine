#include "EventManager.h"
#include "tigr.h"
#include <windows.h>
#include <algorithm>


EventManager* EventManager::s_pInstance = 0;

void EventManager::fireEvent(std::string name,...)
{
	removePendingEvents();
	EventCallbacks* currentEvent = &events[name];
	if (currentEvent->callbacks.size() == 0)
		return;
	std::unordered_map<int, std::function<void(eventData)>>::iterator it = currentEvent->callbacks.begin();


	va_list args;
	eventData parameters = {};
	va_start(args,name);
	switch (currentEvent->parameters)
	{
	case(eventParameterTypes::NONE):
			break;
	case(eventParameterTypes::INT2):
		parameters.int2.i1 = va_arg(args, int);
		parameters.int2.i2 = va_arg(args, int);
			break;
	default:
		break;
	}


	while (it != currentEvent->callbacks.end())
	{
		it->second(parameters);
		it++;
	}
}


EventId EventManager::bindEvent(std::string eventName, eventParameterTypes paramTypes, std::function<void(eventData)> func)
{
	EventCallbacks* currentEvent = &events[eventName];
	currentEvent->parameters = paramTypes;
	EventId newEvent;
	newEvent.name = eventName;
	do{
		newEvent.idNumber = rand();
	} while (currentEvent->callbacks.count(newEvent.idNumber) > 0);

	currentEvent->callbacks[newEvent.idNumber] = func;
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
