#pragma once
#include "ActorComponent.h" 
#include "Actor.h"
#include "EventManager.h"
#include "ActionEngine.h"
extern "C"
{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}


class ScriptInterface : public ActorComponent
{
public:
	ScriptInterface(std::string _path) : path(_path), ActorComponent(TYPE::TICK) {luaVM = ActionEngine::Instance()->getLuaState();}
	~ScriptInterface() 
	{
		lua_pushlightuserdata(luaVM, owner);
		luaL_setmetatable(luaVM, "Actor");
		lua_setglobal(luaVM, "this");
		lua_getglobal(luaVM, "destroyScript");
		lua_pcall(luaVM, 0, 0, 0);
	}
	void(ScriptInterface::*nextFunction)(float dt) = &ScriptInterface::onStart;
	inline void tick(float dt) { (this->*nextFunction)(dt); }

protected:
	lua_State* luaVM;
	std::string path;

	virtual void onTick(float dt)
	{
		lua_pushlightuserdata(luaVM, owner);
		luaL_setmetatable(luaVM, "Actor");
		lua_setglobal(luaVM, "this");

		lua_getglobal(luaVM, "fireFunction");
		lua_pushstring(luaVM, "onTick");
		lua_pushnumber(luaVM, dt);
		lua_pcall(luaVM, 2, 0, 0);
		lua_settop(luaVM, 0);
	}
	virtual void onStart(float dt)
	{

		lua_pushlightuserdata(luaVM, owner);
		luaL_setmetatable(luaVM, "Actor");
		lua_setglobal(luaVM, "this");
		ActionEngine::Instance()->loadLuaScript(path, owner);

		lua_getglobal(luaVM, "fireFunction");
		lua_pushstring(luaVM, "onStart");
		lua_pcall(luaVM, 1, 0,0);
		lua_settop(luaVM, 0);
		nextFunction = &ScriptInterface::onTick;
		onTick(dt);
	}
};