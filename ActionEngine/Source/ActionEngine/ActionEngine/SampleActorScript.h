#pragma once
#include "ScriptInterface.h"
#include "DataInterface.h"

class SampleActorScript : public ScriptInterface
{
private:
	virtual void onTick(Actor *current, float dt);
	virtual void onStart(Actor *current, float dt);
	DataInterface<v2>* actorTransform;
};

