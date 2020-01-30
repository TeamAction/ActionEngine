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
	ScriptInterface(std::string _name) : name(_name), ActorComponent(TYPE::TICK) {
		luaVM = ActionEngine::Instance()->getLuaState();
	}
	void(ScriptInterface::*nextFunction)(float dt) = &ScriptInterface::onStart;
	inline void tick(float dt) { (this->*nextFunction)(dt); }

protected:
	std::string name;
	lua_State* luaVM;
	Actor** luaActorPointer;

	virtual void onTick(float dt)
	{
		luaActorPointer = static_cast<Actor**>(lua_newuserdata(luaVM, sizeof(Actor*)));
		*(luaActorPointer) = owner;
		luaL_setmetatable(luaVM, "Actor");
		lua_setglobal(luaVM, "this");

		lua_pushstring(luaVM, (char*)name.c_str());
		lua_setglobal(luaVM, "currentScope");
		lua_getglobal(luaVM, "fireFunction");
		lua_pushstring(luaVM, "onTick");
		lua_pushnumber(luaVM, dt);
		lua_pcall(luaVM, 2, 0, 0);
		lua_settop(luaVM, 0);
	}
	virtual void onStart(float dt)
	{
		luaActorPointer = static_cast<Actor**>(lua_newuserdata(luaVM, sizeof(Actor*)));
		*(luaActorPointer) = owner;
		luaL_setmetatable(luaVM, "Actor");
		lua_setglobal(luaVM, "this");

		lua_pushstring(luaVM, (char*)name.c_str());
		lua_setglobal(luaVM, "currentScope");
		lua_getglobal(luaVM, "fireFunction");
		lua_pushstring(luaVM, "onStart");
		lua_pcall(luaVM, 1, 0,0);
		lua_settop(luaVM, 0);
		nextFunction = &ScriptInterface::onTick;
		onTick(dt);
	}
};