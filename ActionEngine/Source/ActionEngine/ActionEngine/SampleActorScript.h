#pragma once
#include "ScriptInterface.h"
#include "DataInterface.h"

class SampleActorScript : public ScriptInterface
{
private:
	virtual void onTick(float dt);
	virtual void onStart(float dt);
	DataInterface<v2>* actorTransform;
};

