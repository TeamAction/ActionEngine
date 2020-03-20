#pragma once
#include <unordered_map>
#include <string>
#include "json.hpp"
class Actor;


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
	
	void loadScene();
	void prepareScene(std::string name);
	bool isSceneReady();

protected:
	static SceneManager* s_pInstance;
	SceneManager();
	~SceneManager();

	bool loadScenePending = false;
	std::string sceneName;

	std::unordered_map<std::string, json> parsedJson;
};

