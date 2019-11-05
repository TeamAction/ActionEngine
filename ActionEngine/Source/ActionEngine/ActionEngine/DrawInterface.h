#pragma once
#include "ActorComponent.h" 
#include "drawHelper.h"
#include "Actor.h"

class DrawInterface: public ActorComponent
{
public:
	DrawInterface(int _layer) : ActorComponent(DRAW),layer(_layer) {}
	void(DrawInterface::*nextFunction)(Actor *current, float dt) = &DrawInterface::onStart;
	inline void addObject(Actor *current, float dt) { (this->*nextFunction)(current, dt); }

protected:
	virtual void onAddObject(Actor *current, float dt) = 0;
	virtual void onStart(Actor *current, float dt) = 0;
	int layer;
};