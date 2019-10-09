#pragma once
#include "ActorComponent.h" 
#include "Actor.h"

class ActiveInterface : public ActorComponent
{
public:
	ActiveInterface() : ActorComponent(TICK){}
	virtual void tick(Actor *current, float dt) =0;
};