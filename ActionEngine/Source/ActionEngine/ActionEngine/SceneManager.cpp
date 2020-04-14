
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
	std::vector<Actor*> preservedActors;

	if (sceneRoot) // remove previous scene if it exists
	{
		sceneRoot->flagActorForRemoval();
		sceneRoot->recoverPreservedActors(preservedActors);
		sceneRoot->removeFlaggedActors();
	}
	EventManager::Instance()->removePendingEvents();

	sceneRoot = new Actor("sceneRoot", nullptr); // create new scene root
	ActionEngine::Instance()->actorMap["sceneRoot"] = sceneRoot;

	lua_pushlightuserdata(ActionEngine::Instance()->getLuaState(), sceneRoot);
	luaL_setmetatable(ActionEngine::Instance()->getLuaState(), "Actor");
	lua_setglobal(ActionEngine::Instance()->getLuaState(), "root");

	for (int i = 0; i < preservedActors.size(); i++)
	{
		ActionEngine::Instance()->actorMap[preservedActors[i]->actorName] = preservedActors[i];
		preservedActors[i]->parent = sceneRoot;
		sceneRoot->children.push_back(preservedActors[i]);
	}

	json jsonParse = parsedJson[sceneName];

	std::string name;
	std::string compType;
	Actor* actor;
	for (int i = 0; i < jsonParse.size(); i++)
	{
		name = jsonParse[i]["name"].get<std::string>();
		actor = new Actor(name, ActionEngine::Instance()->actorMap[jsonParse[i]["parent"].get<std::string>()]);
		ActionEngine::Instance()->actorMap[name] = actor;
		for (int q = 0; q < jsonParse[i]["tags"].size(); q++)
		{
			actor->tags.insert(jsonParse[i]["tags"][q].get<std::string>());
		}
		for (int q = 0; q < jsonParse[i]["components"].size(); q++)
		{
			compType = jsonParse[i]["components"][q]["type"].get<std::string>();
			if (compType == "sprite")
			{
				actor->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DrawSprite(Renderer::Instance()->getAnimation(jsonParse[i]["components"][q]["animation"].get<std::string>()), jsonParse[i]["components"][q]["layer"].get<int>()));
			}
			else if (compType == "script")
			{
				actor->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new ScriptInterface(jsonParse[i]["components"][q]["value"].get<std::string>()));
			}
			else if (compType == "data<v2>")
			{
				actor->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new DataInterface<v2>(v2(jsonParse[i]["components"][q]["value"][0].get<int>(), jsonParse[i]["components"][q]["value"][1].get<int>())));
			}
			else if (compType == "rigidBody")
			{
				actor->addComponent(jsonParse[i]["components"][q]["name"].get<std::string>(), new RigidBody(
					v2(jsonParse[i]["components"][q]["value"][0].get<float>(), jsonParse[i]["components"][q]["value"][1].get<float>()),
					jsonParse[i]["components"][q]["value"][2].get<float>(), jsonParse[i]["components"][q]["value"][3].get<float>(),
					jsonParse[i]["components"][q]["value"][4].get<bool>(), v2(jsonParse[i]["components"][q]["value"][5].get<float>(), 
					jsonParse[i]["components"][q]["value"][6].get<float>()), jsonParse[i]["components"][q]["value"][7].get<bool>()));
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
