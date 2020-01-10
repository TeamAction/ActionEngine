#pragma once
#include "ScriptInterface.h"
#include "DataInterface.h"

class SampleActorSpawnScript : public ScriptInterface
{
private:
	virtual void onTick(float dt);
	virtual void onStart(float dt);
	virtual void spaceBarTest();
	DataInterface<v2>* actorTransform = nullptr;
	v2 startPosition;
	float timer = 0;
	EventId test;
};
