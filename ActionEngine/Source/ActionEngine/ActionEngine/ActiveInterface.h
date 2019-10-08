#pragma once
#include "ActorComponent.h" 

class Actor;
class ActiveInterface : public ActorComponent
{
public:
	virtual void tick(Actor *current, float dt) =0;
};