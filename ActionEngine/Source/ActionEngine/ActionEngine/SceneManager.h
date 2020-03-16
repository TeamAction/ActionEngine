#pragma once
#include <unordered_map>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class SceneManager
{
public:
	static SceneManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SceneManager();
		}
		return s_pInstance;
	}
	
	json getSceneData(std::string sceneName);

protected:
	static SceneManager* s_pInstance;
	SceneManager();
	~SceneManager();

	std::unordered_map<std::string, json> parsedJson;
};

