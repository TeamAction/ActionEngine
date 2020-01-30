#pragma once

#include "ActionEngine.h"
#include "Actor.h"
#include "Renderer.h"
#include "InputManager.h"
#include "EventManager.h"
#include "Initialize.h"

#include <iostream>
#include <fstream>

extern "C"
{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}


#include "DrawSprite.h"
#include "json.hpp"
using json = nlohmann::json;


ActionEngine* ActionEngine::s_pInstance = 0;

extern "C" int fireEvent(lua_State* L) { return EventManager::Instance()->fireEvent(L); }
extern "C" int bindEvent(lua_State* L) { return EventManager::Instance()->bindEvent(L); }
extern "C" int unBindEvent(lua_State* L) { return EventManager::Instance()->unBindEvent(L); }
extern "C" int getTransform(lua_State* L) 
{ 
	Actor** actor = static_cast<Actor**>(luaL_checkudata(L, 1, "Actor"));
	v2 transform = (*actor)->getGlobalTransform();
	lua_pushnumber(L, transform.x);
	lua_pushnumber(L, transform.y);
	return 2;
}
extern "C" int setTransform(lua_State* L) 
{ 
	Actor** actor = static_cast<Actor**>(luaL_checkudata(L, 1, "Actor"));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	(*actor)->setGlobalTransform(v2(x,y));
	return 0;
}
extern "C" int screenText(lua_State* L)
{ 
	int x = lua_tointeger(L, 1);
	int y = lua_tointeger(L, 2);
	std::string text = std::string(lua_tostring(L, 3));
	float time = lua_tonumber(L, 4);
	Renderer::Instance()->addScreenText(x, y, (char*)text.c_str(),time);
	lua_settop(L, 0);
	return 0;
}


ActionEngine::ActionEngine()
{
	if (!Initialize::IsOnlyInstance("MyGame", &hHandle))
		return;
	if (!Initialize::CheckAvailibleMemory(300000, 300000)) // memory in kb
		return;
	if (!Initialize::CheckStorage(300)) // memory in mb
		return;
	Initialize::checkSystem();

	luaVM = luaL_newstate();
	luaL_openlibs(luaVM);
	luaL_loadfile(luaVM, "../../../Assets/scripts/loader.lua");
	if (lua_pcall(luaVM, 0, 0, 0))
	{
		Renderer::Instance()->ErrorPopup("lua priming call failed");
	}
	bindLuaFunction("bindEvent",&bindEvent);
	bindLuaFunction("fireEvent",&fireEvent);
	bindLuaFunction("unBindEvent",&unBindEvent);
	bindLuaFunction("screenText",&screenText);

	luaL_newmetatable(luaVM, "Actor");
	lua_pushvalue(luaVM, -1);
	lua_setfield(luaVM, -2, "__index");
	lua_pushcfunction(luaVM, getTransform);
	lua_setfield(luaVM, -2, "getTransform"); 
	lua_pushcfunction(luaVM, setTransform);
	lua_setfield(luaVM, -2, "setTransform"); 
	engineActive = true;
}



ActionEngine::~ActionEngine()
{
	sceneRoot->flagActorForRemoval();
	sceneRoot->removeFlaggedActors();
	delete sceneRoot;
	lua_close(luaVM);
	Initialize::Terminate(&hHandle);
}

bool ActionEngine::isGameActive()
{
	return engineActive && Renderer::Instance()->status();
}

void ActionEngine::play()
{
	bool test = Renderer::Instance()->status();
	Renderer::Instance()->updateTime();
	while (isGameActive())
	{
		Renderer::Instance()->updateTime();
		InputManager::Instance()->fireInputEvents();
		sceneRoot->tick(Renderer::Instance()->getDeltaTime());
		sceneRoot->removeFlaggedActors();
		Renderer::Instance()->draw();
	}
}

void ActionEngine::loadSceneJson(std::string path)
{
	if (sceneRoot) // remove previous scene if it exists
	{
		sceneRoot->flagActorForRemoval();
		sceneRoot->removeFlaggedActors();
		delete sceneRoot; // the scene root cannot be removed by the remove flagged actors method
	}
	sceneRoot = new Actor("SceneRoot", nullptr); // create new scene root

	//std::ifstream input(path); //load json file from provided path
	//json jsonParse;
	//if (!input) //thow error if file failed to load 
	//{
		//Renderer::Instance()->ErrorPopup("JSON file failed to load");
		//return;
	//}
	//input >> jsonParse; // uses an overloaded operator to parse file from iostream
	loadLuaScript("../../../Assets/scripts/testScript.lua", "testScript");
	Actor* temp = new Actor("scriptTester", sceneRoot);
	temp->addComponent("testingBasicScript", new ScriptInterface("testScript"));
	temp->addComponent("transform", new DataInterface<v2>(v2(0,0)));
	temp->addComponent("spriteTest", new DrawSprite(drawObject(1, v2(0, 0), v2(0, 0)), 0));
	temp = new Actor("scriptTester", temp);
	temp->addComponent("testingBasicScript", new ScriptInterface("testScript"));
	temp->addComponent("transform", new DataInterface<v2>(v2(-50, -50)));
	temp->addComponent("spriteTest", new DrawSprite(drawObject(1, v2(0, 0), v2(0, 0)), 0));

	/*
	Actor* temp = new Actor("Mouse Click Spawner", sceneRoot);
	temp->addComponent("testSpawning", new SampleActorMouseClick());
	for (int j = 0; j < HEIGHT / 64 + 1; j++)
	{
		temp = new Actor("Space Bar Spawner", sceneRoot);
		temp->addComponent("testSpawning", new SampleActorSpawnScript());
		temp->addComponent("transform", new DataInterface<v2>(v2(-64.0f, j * 64.0f)));
	
	*/
}

void ActionEngine::loadLuaScript(std::string path, std::string name)
{
	lua_getglobal(luaVM, "luaLoader");
	lua_pushstring(luaVM, (char*)path.c_str());
	lua_pushstring(luaVM, (char*)name.c_str());
	lua_pcall(luaVM, 2, 0,0);
	lua_settop(luaVM, 0);
}

lua_State* ActionEngine::getLuaState()
{
	return luaVM;
}

void ActionEngine::bindLuaFunction(std::string name, lua_CFunction function)
{
	lua_pushcfunction(luaVM, function);
	lua_setglobal(luaVM, (char*)name.c_str());
}

