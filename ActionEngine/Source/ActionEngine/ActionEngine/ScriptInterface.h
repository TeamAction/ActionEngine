#pragma once
#include "ActorComponent.h" 
#include "Actor.h"



class ScriptInterface : public ActorComponent
{
public:
	ScriptInterface() : ActorComponent(TICK) {}
	//tick = &ScriptInterface::onStart;
	void(ScriptInterface::*nextFunction)(Actor *current, float dt) = &ScriptInterface::onStart;
	inline void tick(Actor *current, float dt) { (this->*nextFunction)(current,dt); }
	//void(ScriptInterface::*tick)(Actor *current, float dt);

private:
	virtual void onTick(Actor *current, float dt) = 0;
	virtual void onStart(Actor *current, float dt) = 0;
};