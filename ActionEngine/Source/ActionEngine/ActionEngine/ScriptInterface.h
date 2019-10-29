#pragma once
#include "ActorComponent.h" 
#include "Actor.h"

class ScriptInterface : public ActorComponent
{
public:
	ScriptInterface() : ActorComponent(TICK){}
	virtual void tick(Actor *current, float dt) =0;
};