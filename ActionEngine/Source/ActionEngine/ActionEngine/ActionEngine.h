#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Actor;
struct lua_State;
typedef void *HANDLE;
typedef int (*lua_CFunction) (lua_State* L);


class ActionEngine
{
public:
	static ActionEngine* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new ActionEngine();
		}
		return s_pInstance;
	}

	void play();
	void loadLuaScript(std::string path, Actor* name);
	lua_State* getLuaState();
	void bindLuaFunction(std::string name, lua_CFunction function);

	std::unordered_map<std::string, Actor*> actorMap;
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	bool isGameActive();

	Actor* sceneRoot;
	bool engineActive = false;
	HANDLE hHandle;
	lua_State* luaVM;
	std::unordered_map<std::string, int> luaScopes;
};


