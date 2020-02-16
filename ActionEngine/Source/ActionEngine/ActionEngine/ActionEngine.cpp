#pragma once


#include <iostream> //used to parse json
#include <fstream> 
#include "json.hpp"
using json = nlohmann::json;


#include "ActionEngine.h" //singleton system managers
#include "Renderer.h" 
#include "InputManager.h"
#include "PhysicsSystem.h"



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
		"scriptNamespace[this] = nil "
		"end");
	if (lua_pcall(luaVM, 0, 0, 0))
	{
		Renderer::Instance()->ErrorPopup("lua priming call failed");
	}
	bindLuaFunction("bindEvent",&bindEvent);
	bindLuaFunction("fireEvent",&fireEvent);
	bindLuaFunction("unBindEvent",&unBindEvent);
	bindLuaFunction("screenText",&screenText);
	bindLuaFunction("keyDown",&keyDown);
	bindLuaFunction("keyUp",&keyUp);
	bindLuaFunction("keyHeld",&keyHeld);
	bindLuaFunction("mousePosition",&mousePosition);
	bindLuaFunction("mouseButtons",&mouseButtons);
	bindLuaFunction("loadScene",&loadScene);

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

void ActionEngine::loadScenePostTick()
{
	loadScenePending = false;
	std::unordered_map<std::string, Actor*> actorMap;
	if (sceneRoot) // remove previous scene if it exists
	{
		sceneRoot->flagActorForRemoval();
		sceneRoot->removeFlaggedActors();
		delete sceneRoot; // the scene root cannot be removed by the remove flagged actors method
	}
	sceneRoot = new Actor("sceneRoot", nullptr); // create new scene root
	actorMap["sceneRoot"] = sceneRoot;

	std::ifstream input(sceneFile); //load json file from provided path
	json jsonParse;
	if (!input) //thow error if file failed to load 
	{
		Renderer::Instance()->ErrorPopup("JSON file failed to load");
		return;
	}
	input >> jsonParse; // uses an overloaded operator to parse file from iostream

	std::string name;
	std::string compType;
	for (int i = 0; i < jsonParse.size(); i++)
	{
		name = jsonParse[i]["name"].get<std::string>();
		actorMap[name] = new Actor(name, actorMap[jsonParse[i]["parent"].get<std::string>()]);
		for (int q = 0; q < jsonParse[i]["components"].size(); q++)
		{
			compType = jsonParse[i]["components"][q]["type"].get<std::string>();
			if (compType == "sprite")
			{
				std::vector<drawObject> animFrames;
				int numFrames = jsonParse[i]["components"][q]["frames"].size();
				for (int z = 0; z < numFrames; z++)
				{
					animFrames.push_back(drawObject(jsonParse[i]["components"][q]["frames"][z].get<int>()));
				}
				actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DrawSprite(animFrames, jsonParse[i]["components"][q]["layer"].get<int>(), 1.5f));
			}
			else if (compType == "script")
			{
				actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new ScriptInterface(jsonParse[i]["components"][q]["value"].get<std::string>()));
			}
			else if (compType == "data<v2>")
			{
				actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DataInterface<v2>(v2(jsonParse[i]["components"][q]["value"][0].get<int>(), jsonParse[i]["components"][q]["value"][1].get<int>())));
			}
			else if (compType == "rigidBody")
			{
				actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new RigidBody(
					v2(jsonParse[i]["components"][q]["value"][0].get<float>(), jsonParse[i]["components"][q]["value"][1].get<float>()),
					jsonParse[i]["components"][q]["value"][2].get<float>(), jsonParse[i]["components"][q]["value"][3].get<float>(),
					jsonParse[i]["components"][q]["value"][4].get<bool>(), v2(jsonParse[i]["components"][q]["value"][5].get<float>(), jsonParse[i]["components"][q]["value"][6].get<float>())));
			}
		}
	}
}

void ActionEngine::play()
{
	bool test = Renderer::Instance()->status();
	Renderer::Instance()->updateTime();
	while (isGameActive())
	{
		if (loadScenePending)
			loadScenePostTick();
		Renderer::Instance()->updateTime();
		InputManager::Instance()->updateInputState();
		sceneRoot->tick(Renderer::Instance()->getDeltaTime());
		PhysicsSystem::Instance()->UpdatePhysics(0.016f);
		sceneRoot->removeFlaggedActors();
		Renderer::Instance()->draw();
	}
}

void ActionEngine::loadSceneJson(std::string path)
{
	sceneFile = path;
	loadScenePending = true;
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

