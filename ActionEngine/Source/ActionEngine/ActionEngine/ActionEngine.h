#pragma once
#include "Actor.h"

class ActionEngine
{
public:
	ActionEngine();
	~ActionEngine();
	bool active();
	void tick();
private:
	bool engineActive;
	std::vector<Actor> activeActors;
};

