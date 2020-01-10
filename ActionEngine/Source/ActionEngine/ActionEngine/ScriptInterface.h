#pragma once
#include "ActorComponent.h" 
#include "Actor.h"
#include "EventManager.h"



class ScriptInterface : public ActorComponent
{
public:
	ScriptInterface() : ActorComponent(TYPE::TICK) {}
	void(ScriptInterface::*nextFunction)(float dt) = &ScriptInterface::onStart;
	inline void tick(float dt) { (this->*nextFunction)(dt); }

protected:
	virtual void onTick(float dt) = 0;
	virtual void onStart(float dt) = 0;
};