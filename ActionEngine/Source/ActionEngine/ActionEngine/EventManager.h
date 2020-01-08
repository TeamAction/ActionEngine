#pragma once
#include <unordered_map>
#include <functional>
#include <Windows.h>

struct Tigr;

enum eventParameterTypes {
	NONE,
	INT2
};

typedef union eventData{
	struct int2 { int i1, i2;}int2;
};

struct EventCallbacks
{
	std::unordered_map<int, std::function<void(eventData)>> callbacks; //callback id , callback
	eventParameterTypes parameters = NONE;
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
	void fireEvent(std::string name,...);
	EventId bindEvent(std::string, eventParameterTypes paramTypes,std::function<void(eventData)> func);
	void unBindEvent(EventId);
};
