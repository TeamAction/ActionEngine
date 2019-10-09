#pragma once
#include "ActiveInterface.h"
#include "DrawInterface.h"
#include "DataInterface.h"

class SampleActorScript : public ActiveInterface
{
public:
	SampleActorScript();
	~SampleActorScript();
	virtual void tick(Actor *current, float dt);
private:
	DataInterface<v2>* actorTransform;
};

