#pragma once


#include <iostream> //used to parse json
#include <fstream> 
#include "json.hpp"
using json = nlohmann::json;


#include "ActionEngine.h" //singleton system managers
#include "Renderer.h" 
#include "InputManager.h"
#include "PhysicsSystem.h"
#include "sceneManager.h"
#include "EventManager.h"

#include "Actor.h" // actor object 

#include "DrawSprite.h" //actor components
#include "ScriptInterface.h"
#include "RigidBody.h"
#include "DataInterface.h"


#include "LuaInterfaceFucntions.h" //seperated file to help keep oranisation
#include "Initialize.h" //static class containing methods to check computer status before startup

extern "C" // lua interpreter
{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}

ActionEngine* ActionEngine::s_pInstance = 0;



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
	luaL_loadstring(luaVM, "scriptNamespace = {} "
		"function fireFunction(functionName, ...) "
		"return (scriptNamespace[this][functionName](...)) "
		"end "
		"function luaLoader(path) "
		"scriptNamespace[this] = setmetatable({}, { __index = _G }) "
		"local chunk = loadfile(path, nil, scriptNamespace[this]) "
		"chunk() "
		"end "
		"function destroyScript() "
		"unBindAll(this) "
		"scriptNamespace[this] = nil "
		"end");
	if (lua_pcall(luaVM, 0, 0, 0))
	{
		Renderer::Instance()->ErrorPopup("lua priming call failed");
	}
	bindLuaFunction("bindEvent",&bindEvent);
	bindLuaFunction("fireEvent",&fireEvent);
	bindLuaFunction("unBindEvent",&unBindEvent);
	bindLuaFunction("unBindAll",&unBindAll);
	bindLuaFunction("screenText",&screenText);
	bindLuaFunction("keyDown",&keyDown);
	bindLuaFunction("keyUp",&keyUp);
	bindLuaFunction("keyHeld",&keyHeld);
	bindLuaFunction("mousePosition",&mousePosition);
	bindLuaFunction("mouseButtons",&mouseButtons);
	bindLuaFunction("loadScene",&loadScene);
	bindLuaFunction("getActorByName",&getActorByName);

	luaL_newmetatable(luaVM, "Actor");
	lua_pushvalue(luaVM, -1);
	lua_setfield(luaVM, -2, "__index");
	lua_pushcfunction(luaVM, getGlobalTransform);
	lua_setfield(luaVM, -2, "getGlobalTransform"); 
	lua_pushcfunction(luaVM, setGlobalTransform);
	lua_setfield(luaVM, -2, "setGlobalTransform"); 
	lua_pushcfunction(luaVM, getLocalTransform);
	lua_setfield(luaVM, -2, "getLocalTransform"); 
	lua_pushcfunction(luaVM, setLocalTransform);
	lua_setfield(luaVM, -2, "setLocalTransform"); 
	lua_pushcfunction(luaVM, addImpulse);
	lua_setfield(luaVM, -2, "addImpulse"); 
	lua_pushcfunction(luaVM, getVelocity);
	lua_setfield(luaVM, -2, "getVelocity"); 
	lua_pushcfunction(luaVM, isGrounded);
	lua_setfield(luaVM, -2, "isGrounded"); 
	lua_pushcfunction(luaVM, destroyActor);
	lua_setfield(luaVM, -2, "destoryActor"); 
	lua_pushcfunction(luaVM, createActor);
	lua_setfield(luaVM, -2, "createActor"); 
	lua_pushcfunction(luaVM, attachTransform);
	lua_setfield(luaVM, -2, "attachTransform"); 
	lua_pushcfunction(luaVM, attachScript);
	lua_setfield(luaVM, -2, "attachScript"); 
	lua_pushcfunction(luaVM, attachSprite);
	lua_setfield(luaVM, -2, "attachSprite"); 
	lua_pushcfunction(luaVM, setPreserveInTransition);
	lua_setfield(luaVM, -2, "setPreserveInTransition"); 

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
		if (SceneManager::Instance()->isSceneReady())
		{
			SceneManager::Instance()->loadScene();
			sceneRoot = actorMap["sceneRoot"];
		}
		Renderer::Instance()->updateTime();
		InputManager::Instance()->updateInputState();
		sceneRoot->tick(Renderer::Instance()->getDeltaTime());
		PhysicsSystem::Instance()->UpdatePhysics(0.016f);
		sceneRoot->removeFlaggedActors();
		Renderer::Instance()->draw();
	}
}

void ActionEngine::loadLuaScript(std::string path, Actor* name)
{
	lua_getglobal(luaVM, "luaLoader");
	lua_pushstring(luaVM, (char*)path.c_str());
	lua_pcall(luaVM, 1, 0,0);
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
