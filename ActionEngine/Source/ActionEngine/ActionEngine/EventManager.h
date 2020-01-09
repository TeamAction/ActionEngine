#pragma once
#include <unordered_map>
#include <functional>
#include <Windows.h>
#include <algorithm>

template <typename ...Args>
struct EventCallbacks
{
	std::unordered_map<int, std::function<void(Args...)>> callbacks; //callback id , callback
};

struct EventId 
{
	std::string name;
	int idNumber;
};


template <typename ...Args>
class EventManager
{
private:
	static EventManager<Args...>* s_pInstance;
	EventManager() {}
	typename std::unordered_map<std::string, EventCallbacks<Args...>> events; //event name, callback list
	std::vector<EventId> pendingRemoval;
	void removePendingEvents()
	{
		for (int i = 0; i < pendingRemoval.size(); i++)
		{
			events[pendingRemoval[i].name].callbacks.erase(pendingRemoval[i].idNumber);
		}
		pendingRemoval.clear();
	}
public:	
	static EventManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new EventManager<Args...>();
		}
		return s_pInstance;
	}

	void fireEvent(std::string name, Args ...args)
	{
		removePendingEvents();
		EventCallbacks<Args...>* currentEvent = &events[name];
		if (currentEvent->callbacks.size() == 0)
			return;

		typename std::unordered_map<int, typename std::function<void(Args...)>>::iterator it = currentEvent->callbacks.begin();
		while (it != currentEvent->callbacks.end())
		{
			it->second(args...);
			it++;
		}
	}

	EventId bindEvent(std::string eventName, std::function<void(Args...)> func)
	{
		EventCallbacks<Args...>* currentEvent = &events[eventName];
		EventId newEvent;
		newEvent.name = eventName;
		do {
			newEvent.idNumber = rand();
		} while (currentEvent->callbacks.count(newEvent.idNumber) > 0);

		currentEvent->callbacks[newEvent.idNumber] = func;
		return newEvent;
	}
	void unBindEvent(EventId id) 
	{
		pendingRemoval.push_back(id);
	}
};

EventManager<>* EventManager<>::s_pInstance = nullptr;
EventManager<int, int>* EventManager<int, int>::s_pInstance = nullptr;
