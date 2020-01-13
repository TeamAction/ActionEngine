#pragma once
#include <vector>

//forward declared classes and structs
struct Tigr;
class Actor;
struct v2;
struct Sprite;
struct drawObject;
typedef void *HANDLE;

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
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	void createSampleActor();
	bool isGameActive();
	Actor* sceneRoot;
	bool engineActive = false;
	HANDLE hHandle;
};


