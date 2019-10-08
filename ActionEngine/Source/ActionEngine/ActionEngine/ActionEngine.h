#pragma once
#include "Actor.h"
#include "tigr.h"
#include "cute_c2.h"


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


	bool isGameActive();
	void tick();
	void draw();
private:
	static ActionEngine* s_pInstance;

	ActionEngine();
	~ActionEngine();

	bool engineActive;
	float frameTime;
	Tigr *screen;
	std::vector<Actor> activeActors;
};

