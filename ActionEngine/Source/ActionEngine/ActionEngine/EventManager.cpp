#pragma once
#include "EventManager.h"

EventManager* EventManager::s_pInstance = 0;

void EventManager::removePendingEvents()
{
	for (int i = 0; i < pendingRemoval.size(); i++)
	{
		events[pendingRemoval[i].first].erase(pendingRemoval[i].second);
	}
	pendingRemoval.clear();
}

int EventManager::fireEvent(lua_State* L)
{
	removePendingEvents();

	int numberOfArgs = lua_gettop(L);
	std::string eventName = std::string(lua_tostring(L, 2));
	std::unordered_map<Actor*, std::pair<std::string, std::string>>::iterator it = events[eventName].begin();
	
	while(it != events[eventName].end())
	{
		lua_pushlightuserdata(L, it->first);
		luaL_setmetatable(L, "Actor");
		lua_setglobal(L, "this");

		lua_pushstring(L, (char*)it->second.first.c_str());
		lua_setglobal(L, "currentScope");
		lua_getglobal(L, "fireFunction");
		lua_pushstring(L, (char*)it->second.second.c_str());
		for (int i = 3; i <= numberOfArgs; i++)
		{
			int t = lua_type(L, i);
			switch (t) {
			case LUA_TSTRING: 
				lua_pushstring(L,lua_tostring(L, i));
				break;
			case LUA_TBOOLEAN:
				lua_pushboolean(L, lua_toboolean(L, i));
				break;
			case LUA_TNUMBER:
				lua_pushnumber(L, lua_tonumber(L, i));
				break;
			}
		}
		lua_pcall(L,numberOfArgs-1, 0, 0);
		it++;
	}
	lua_settop(L, 0);
	return 0;
}

int EventManager::bindEvent(lua_State* L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	std::string eventName = std::string(lua_tostring(L, 2));
	std::string functionName = std::string(lua_tostring(L, 3));

	lua_getglobal(L, "currentScope");
	std::string scopeName = std::string(lua_tostring(L, -1));

	std::pair<std::string, std::string> function(scopeName, functionName);

	events[eventName][actor] = function;
	lua_settop(L, 0);
	return 0;
}

int EventManager::unBindEvent(lua_State* L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	std::string eventName = std::string(lua_tostring(L, 2));

	std::pair<std::string, Actor*> pendingErasure(eventName, actor);

	pendingRemoval.push_back(pendingErasure);
	lua_settop(L, 0);
	return 0;
}
