#pragma once
#include "ActorComponent.h" 
#include "Actor.h"



class ScriptInterface : public ActorComponent
{
public:
	ScriptInterface() : ActorComponent(TICK) {}
	void(ScriptInterface::*nextFunction)(Actor *current, float dt) = &ScriptInterface::onStart;
	inline void tick(Actor *current, float dt) { (this->*nextFunction)(current,dt); }

protected:
	virtual void onTick(Actor *current, float dt) = 0;
	virtual void onStart(Actor *current, float dt) = 0;
};