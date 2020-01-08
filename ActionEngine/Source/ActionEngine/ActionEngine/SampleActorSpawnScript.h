#pragma once
#include "ScriptInterface.h"
#include "DataInterface.h"

class SampleActorSpawnScript : public ScriptInterface
{
private:
	virtual void onTick(Actor *current, float dt);
	virtual void onStart(Actor *current, float dt);
	virtual void spaceBarTest();
	DataInterface<v2>* actorTransform;
	float timer = 0;
	EventId test;
};
