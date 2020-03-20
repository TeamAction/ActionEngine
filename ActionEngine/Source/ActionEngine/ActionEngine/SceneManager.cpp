
#include "SceneManager.h"
#include "Actor.h"
#include "Renderer.h"
#include "EventManager.h"
#include "ActionEngine.h"
#include "DrawSprite.h" //actor components
#include "ScriptInterface.h"
#include "RigidBody.h"
#include "DataInterface.h"
#include <iostream> //used to parse json
#include <fstream> 

SceneManager* SceneManager::s_pInstance = 0;

void SceneManager::loadScene()
{
	loadScenePending = false;
	Actor* sceneRoot = ActionEngine::Instance()->actorMap["sceneRoot"];
	if (sceneRoot) // remove previous scene if it exists
	{
		sceneRoot->flagActorForRemoval();
		sceneRoot->removeFlaggedActors();
		delete sceneRoot; // the scene root cannot be removed by the remove flagged actors method
	}
	EventManager::Instance()->removePendingEvents();

	sceneRoot = new Actor("sceneRoot", nullptr); // create new scene root
	ActionEngine::Instance()->actorMap["sceneRoot"] = sceneRoot;

	lua_pushlightuserdata(ActionEngine::Instance()->getLuaState(), sceneRoot);
	luaL_setmetatable(ActionEngine::Instance()->getLuaState(), "Actor");
	lua_setglobal(ActionEngine::Instance()->getLuaState(), "root");

	json jsonParse = parsedJson[sceneName];

	std::string name;
	std::string compType;
	for (int i = 0; i < jsonParse.size(); i++)
	{
		name = jsonParse[i]["name"].get<std::string>();
		ActionEngine::Instance()->actorMap[name] = new Actor(name, ActionEngine::Instance()->actorMap[jsonParse[i]["parent"].get<std::string>()]);
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
				ActionEngine::Instance()->actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DrawSprite(animFrames, jsonParse[i]["components"][q]["layer"].get<int>(), jsonParse[i]["components"][q]["loopTime"].get<float>()));
			}
			else if (compType == "script")
			{
				ActionEngine::Instance()->actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new ScriptInterface(jsonParse[i]["components"][q]["value"].get<std::string>()));
			}
			else if (compType == "data<v2>")
			{
				ActionEngine::Instance()->actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DataInterface<v2>(v2(jsonParse[i]["components"][q]["value"][0].get<int>(), jsonParse[i]["components"][q]["value"][1].get<int>())));
			}
			else if (compType == "rigidBody")
			{
				ActionEngine::Instance()->actorMap[name]->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new RigidBody(
					v2(jsonParse[i]["components"][q]["value"][0].get<float>(), jsonParse[i]["components"][q]["value"][1].get<float>()),
					jsonParse[i]["components"][q]["value"][2].get<float>(), jsonParse[i]["components"][q]["value"][3].get<float>(),
					jsonParse[i]["components"][q]["value"][4].get<bool>(), v2(jsonParse[i]["components"][q]["value"][5].get<float>(), jsonParse[i]["components"][q]["value"][6].get<float>())));
			}
		}
	}
}

void SceneManager::prepareScene(std::string name)
{
	sceneName = name;
	loadScenePending = true;
}

bool SceneManager::isSceneReady()
{
	return loadScenePending;
}

SceneManager::SceneManager()
{
	std::ifstream input("../../../Assets/scenes/sceneList.json");
	json jsonParse;
	if (!input)
	{
		Renderer::Instance()->ErrorPopup("JSON file failed to load");
		return;
	}

	input >> jsonParse;

	std::string name;
	std::string path;
	for (int i = 0; i < jsonParse.size(); i++)
	{
		name = jsonParse[i]["name"].get<std::string>();
		path = jsonParse[i]["file"].get<std::string>();
		std::ifstream file(path);
		if (!file)
		{
			Renderer::Instance()->ErrorPopup("JSON file failed to load");
			return;
		}
		json sceneFileParsed;
		file >> sceneFileParsed;
		parsedJson[name] = sceneFileParsed;
	}
}

SceneManager::~SceneManager()
{
}
