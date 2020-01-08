#pragma once
#include <unordered_map>
#include <functional>
#include <Windows.h>

struct Tigr;

//template <typename ...>
struct EventCallbacks
{
	std::unordered_map<int, std::function<void()>> callbacks; //callback id , callback
};

struct EventId 
{
	std::string name;
	int idNumber;
};

class EventManager
{
private:
	static EventManager* s_pInstance;
	EventManager() {}
	std::unordered_map<std::string, EventCallbacks> events; //event name, callback list
	std::vector<EventId> pendingRemoval;
	void removePendingEvents();
public:	
	static EventManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new EventManager();
		}
		return s_pInstance;
	}

	void fireEvent(std::string name);
	EventId bindEvent(std::string, std::function<void()> func);
	void unBindEvent(EventId);
};

