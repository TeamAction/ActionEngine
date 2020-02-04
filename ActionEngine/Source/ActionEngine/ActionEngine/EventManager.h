#pragma once
#include <unordered_map>
#include <algorithm>
#include <utility>

extern "C"
{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
class Actor;
class EventManager
{
private:
	static EventManager* s_pInstance;
	EventManager() {}
	~EventManager() {delete s_pInstance;s_pInstance = nullptr;}
	std::unordered_map<std::string, std::unordered_map<Actor*,std::string>> events; //event name , owning actor <scope,function>
	std::vector<std::pair<std::string, Actor*>> pendingRemoval; //eventName,owning actor
	
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

	int fireEvent(lua_State* L);

	int bindEvent(lua_State* L);

	int unBindEvent(lua_State* L);
};