
#include "SceneManager.h"
#include "Renderer.h" 
#include <iostream> //used to parse json
#include <fstream> 

SceneManager* SceneManager::s_pInstance = 0;

json SceneManager::getSceneData(std::string sceneName)
{
	return parsedJson[sceneName];
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
