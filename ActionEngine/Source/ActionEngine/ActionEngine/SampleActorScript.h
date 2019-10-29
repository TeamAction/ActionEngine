#pragma once
#include "ScriptInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"

class SampleActorScript : public ScriptInterface
{
public:
	SampleActorScript(Actor * current);
	~SampleActorScript();
	virtual void tick(Actor *current, float dt);
private:
	DataInterface<v2>* actorTransform;
};

