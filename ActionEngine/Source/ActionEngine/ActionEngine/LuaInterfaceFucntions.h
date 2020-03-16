#pragma once
extern "C"
{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#include "Actor.h"
#include "Renderer.h"
#include "InputManager.h"
#include "EventManager.h"
#include "ActionEngine.h"

extern "C" int fireEvent(lua_State * L) { return EventManager::Instance()->fireEvent(L); }
extern "C" int bindEvent(lua_State * L) { return EventManager::Instance()->bindEvent(L); }
extern "C" int unBindEvent(lua_State * L) { return EventManager::Instance()->unBindEvent(L); }
extern "C" int unBindAll(lua_State * L) {
	return EventManager::Instance()->unBindAll(L); 
}
extern "C" int getGlobalTransform(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	v2 transform = actor->getGlobalTransform();
	lua_pushnumber(L, transform.x);
	lua_pushnumber(L, transform.y);
	return 2;
}
extern "C" int setGlobalTransform(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	float x = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -1);
	actor->setGlobalTransform(v2(x, y));
	return 0;
}
extern "C" int getLocalTransform(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	v2 transform = actor->getLocalTransform();
	lua_pushnumber(L, transform.x);
	lua_pushnumber(L, transform.y);
	return 2;
}
extern "C" int setLocalTransform(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	float x = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -1);
	actor->setLocalTransform(v2(x, y));
	return 0;
}
extern "C" int addImpulse(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	float x = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -1);
	actor->addForce(v2(x, y) /0.016f);
	return 0;
}

extern "C" int getVelocity(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	v2 velocity = actor->getVelocity();
	lua_pushnumber(L, velocity.x);
	lua_pushnumber(L, velocity.y);
	return 2;
}

extern "C" int isGrounded(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	lua_pushboolean(L, actor->isGrounded());
	return 1;
}
extern "C" int screenText(lua_State * L)
{
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	std::string text = std::string(lua_tostring(L, 3));
	float time = lua_tonumber(L, 4);
	Renderer::Instance()->addScreenText(x, y, (char*)text.c_str(), time);
	lua_settop(L, 0);
	return 0;
}

extern "C" int keyUp(lua_State * L) { lua_pushboolean(L, InputManager::Instance()->getKeyUp(toupper(*lua_tostring(L, 1)))); return 1; }
extern "C" int keyDown(lua_State * L){lua_pushboolean(L, InputManager::Instance()->getKeyDown(toupper(*lua_tostring(L, 1))));return 1;}
extern "C" int keyHeld(lua_State * L) { lua_pushboolean(L, InputManager::Instance()->getKeyHeld(toupper(*lua_tostring(L, 1)))); return 1; }

extern "C" int mousePosition(lua_State * L)
{
	lua_pushnumber(L, InputManager::Instance()->getMouseX());
	lua_pushnumber(L, InputManager::Instance()->getMouseY());
	return 2;
}

extern "C" int mouseButtons(lua_State * L)
{
	lua_pushboolean(L, InputManager::Instance()->getMouseLeftButton());
	lua_pushboolean(L, InputManager::Instance()->getMouseRightButton());
	return 2;
}

extern "C" int loadScene(lua_State * L){ActionEngine::Instance()->loadSceneJson(lua_tostring(L, 1));return 0;}

extern "C" int getActorByName(lua_State * L)
{
	const char* actorName = lua_tostring(L, 1);
	Actor* test = ActionEngine::Instance()->actorMap["platform2"];
	if(ActionEngine::Instance()->actorMap.count(actorName) == 1)
		lua_pushlightuserdata(L,ActionEngine::Instance()->actorMap[actorName]);
	else
	{
		lua_pushlightuserdata(L, ActionEngine::Instance()->actorMap["sceneRoot"]);
		char output[256];
		sprintf_s(output, "requested actor \"%s\" not found", actorName);
		Renderer::Instance()->ErrorPopup(output);
	}
	return 1;
}

extern "C" int destroyActor(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	actor->flagActorForRemoval();
	return 0;
}

extern "C" int createActor(lua_State * L)
{
	Actor* parent = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	const char* name = lua_tostring(L, 2);
	ActionEngine::Instance()->actorMap[name] = new Actor(name, parent);
	lua_pushlightuserdata(L, ActionEngine::Instance()->actorMap[name]);
	return 1;
}

extern "C" int attachScript(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	const char* name = lua_tostring(L, 2);
	const char* path = lua_tostring(L, 3);
	actor->addComponent(name, new ScriptInterface(path));
	return 0;
}

extern "C" int attachTransform(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	actor->addComponent("transform", new DataInterface<v2>(v2(0, 0)));
	return 0;
}

extern "C" int attachSprite(lua_State * L)
{
	Actor* actor = static_cast<Actor*>(luaL_checkudata(L, 1, "Actor"));
	const int layer = lua_tointeger(L, 2);
	const float loopTime = lua_tonumber(L, 3);
	int numFrames = lua_gettop(L);

	std::vector<drawObject> animFrames;
	for (int i = 4; i < numFrames; i++)
	{
		animFrames.push_back(drawObject(lua_tointeger(L, i)));
	}
	actor->addComponent("sprite", new DrawSprite(animFrames, layer, loopTime));
	return 0;
}

