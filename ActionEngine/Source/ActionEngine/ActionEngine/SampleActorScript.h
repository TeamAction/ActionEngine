#pragma once
#include "ActiveInterface.h"
class SampleActorScript : public ActiveInterface
{
public:
	SampleActorScript();
	~SampleActorScript();
	virtual void tick(Actor *current, float dt);
};

